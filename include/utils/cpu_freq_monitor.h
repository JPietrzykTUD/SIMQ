/* 
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
 * Copyright (c) 2020 Alexander Krause.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TUDDBS_SIMQ_INCLUDE_UTILS_CPU_FREQ_MONITOR_H
#define TUDDBS_SIMQ_INCLUDE_UTILS_CPU_FREQ_MONITOR_H

#include <thread>
#include <utils/definitions.h>
#include <utils/md_singleton.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <string>
#include <sstream>

namespace tuddbs {
	class cpu_freq_monitor : public singleton< cpu_freq_monitor > {
	public:
		 friend class singleton< cpu_freq_monitor >;
		 friend class thread;
	private:
		cpu_freq_monitor( void ) {
		}

		void init( void ) {
		}

		void frequency_monitoring() {
			using namespace std::chrono_literals;
			size_t tick = 0;
			/* Prepare and init */
			auto last_tick_time = now();
			auto curr_tick_time = now();
			while (!halt) {
				last_tick_time = now();
				read_frequencies( last_core_count, tick );
				++tick;
				/* We need to enlarge the array, just in case more measurements come in... */
				if ( tick >= last_expected_ticks ) {
					last_expected_ticks *= 2;
					for ( size_t i = 0; i < last_core_count; ++i ) {
						freq_array[i] = (uint64_t*) realloc( freq_array[i], sizeof( uint64_t ) * last_expected_ticks );
					}
				}

				curr_tick_time = now();
				auto diff = std::chrono::duration_cast< std::chrono::milliseconds >( curr_tick_time - last_tick_time );
				/* 
					Try to start measuring approx. every "resolution" ms. However, we do not yet 
					consider what happens if measuring takes longer than resolution.
				*/
				std::this_thread::sleep_for( resolution - std::chrono::milliseconds( diff.count() ) );
			}
			registered_ticks = tick;
		}
		
		/* Reading frequencies of cores [0,core_count] */
		void read_frequencies( const size_t core_count, const size_t tick ) {
			for ( size_t i = 0; i < core_count; ++i ) {
				snprintf(fname_buffer, 57, "/sys/devices/system/cpu/cpu%lu/cpufreq/scaling_cur_freq", i);
				FILE *f = fopen(fname_buffer, "rb");
				fseek(f, 0, SEEK_END);
				long fsize = ftell(f);
				fseek(f, 0, SEEK_SET);
				char* string = (char*) malloc(fsize + 1);
				[[maybe_unused]] int res = fread(string, 1, fsize, f);
				fclose(f);
				string[fsize] = 0;
				freq_array[ i ][ tick ] = atoi( string );
			}
		}

		uint64_t** freq_array;
		char fname_buffer[60];
		bool first_init = true;
		uint64_t last_core_count = 0;
		uint64_t last_expected_ticks = 0;
		uint64_t registered_ticks = 0;
		bool halt = false;
		std::thread* monitor = nullptr;
		std::chrono::milliseconds resolution = std::chrono::milliseconds( 500 );

	public:
		void init( const size_t core_count, const size_t expected_ticks ) {
			if (!first_init) {
				for ( size_t i = 0; i < last_core_count; ++i ) {
					free( freq_array[i] );
				}
				free( freq_array );
			}
			freq_array = (uint64_t**) malloc( sizeof( uint64_t* ) * core_count );

			for ( size_t i = 0; i < core_count; ++i ) {
				freq_array[i] = (uint64_t*) malloc( sizeof( uint64_t ) * expected_ticks );
			}
			last_core_count = core_count;
			last_expected_ticks = expected_ticks;
			first_init = false;
			/* The first read is always slow. To allow for fast access, we prime the file access. */
			read_frequencies( core_count, 0 );
		}
		
		void start_monitoring() {
			if ( monitor != nullptr ) {
				std::cerr << "[ERROR] CPU_FREQ_MONITOR ALREADY RUNNING! STOPPING AND RESTARTING NOW!" << std::endl;
				stop_monitoring();
			}
			halt = false;
			monitor = new std::thread(&cpu_freq_monitor::frequency_monitoring, cpu_freq_monitor::instance());
		}
		
		void stop_monitoring() {
			halt = true;
			monitor->join();
			delete monitor;
			monitor = nullptr;
		}
		
		std::chrono::milliseconds get_resolution() const {
			return resolution;
		}
		
		void set_resolution( std::chrono::milliseconds res ) {
			resolution = res;
		}
		
		std::string get_data() const {
			std::stringstream ss;
			for ( size_t i = 0; i < last_core_count; ++i ) {
				ss << "Core" << i << "@";
				for ( size_t j = 0; j < registered_ticks; ++j ) {
					ss << freq_array[i][j];
					if ( j != registered_ticks - 1 ) {
						ss << "|";
					}
				}
				ss << "\n";
			}
			return ss.str();
		}
	};

}

#endif //TUDDBS_SIMQ_INCLUDE_UTILS_CPU_FREQ_MONITOR_H
