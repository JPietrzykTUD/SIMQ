/* 
 * This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
 * Copyright (c) 2020 Johannes Pietrzyk.
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
#ifndef TUDDBS_SIMQ_INCLUDE_UTILS_HELPER_H
#define TUDDBS_SIMQ_INCLUDE_UTILS_HELPER_H

#include <random>
#include <cstdint>
#include <cstddef>
#include <limits>
#include <utils/definitions.h>
#include <utils/md_singleton.h>

namespace tuddbs {
   std::size_t const cache_flush_size = 32_MiB;
   uint64_t * cache_flush_helper = new uint64_t[cache_flush_size / sizeof( uint64_t )];
   
   class cache_flusher :
      public singleton< cache_flusher > {
      public:
         friend class singleton< cache_flusher >;
      
      private:
         std::mt19937_64                             rnd_engine;
         std::uniform_int_distribution <std::size_t> distribution;
         
         cache_flusher( void ) :
            rnd_engine{ 0xC004C0FEEBADC0DE },
            distribution{ 0, std::numeric_limits< uint64_t >::max( ) - 1 } {
         }
         
         uint64_t aggregate( void ) {
            uint64_t       result = 0;
            for(
               std::size_t i      = 0; i < cache_flush_size / sizeof( uint64_t ); ++i
               ) {
               result ^= cache_flush_helper[ i ];
            }
            return result;
         }
      
      public:
         uint64_t flush( void ) {
            for(
               std::size_t i = 0; i < cache_flush_size / sizeof( uint64_t ); ++i
               ) {
               cache_flush_helper[ i ] ^= distribution( rnd_engine );
            }
            return aggregate( );
         }
   };
   
   struct stride_range {
      std::string identifier;
      std::size_t lower_bound;
      std::size_t upper_bound;
   };
   
   struct stride_generator {
      std::vector <stride_range> stride_ranges;
      
      stride_generator( std::initializer_list <stride_range> l ) :
         stride_ranges{ l } { }
      
      std::vector <stride_range> get_possible_strides( std::size_t data_size ) const {
         std::vector <stride_range> result;
         for(
            auto                    stride_range : stride_ranges
            ) {
            if( data_size > stride_range.upper_bound ) {
               result.push_back( stride_range );
            }
         }
         return result;
      }
   };
}

#endif //TUDDBS_SIMQ_INCLUDE_UTILS_HELPER_H
