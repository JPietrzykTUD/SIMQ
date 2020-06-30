'''
This file is part of the SIMQ Project (https://github.com/JPietrzykTUD/SIMQ).
Copyright (c) 2020 Johannes Pietrzyk.

This program is free software: you can redistribute it and/or modify  
it under the terms of the GNU General Public License as published by  
the Free Software Foundation, version 3.

This program is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
General Public License for more details.

You should have received a copy of the GNU General Public License 
along with this program. If not, see <http://www.gnu.org/licenses/>.
'''
import os
import sys
from glob import glob
from pathlib import Path
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
import matplotlib.ticker as ticker
import matplotlib as mpl
import numpy as np
import math
import matplotlib.font_manager as font_manager
import itertools
from PIL import Image


sns.set_style("white")
sns.set_context("paper")


def create_figure_varying_vector_sizes( dataframe, legend, batch_size=None ):
   df_varying_vector_sizes = pd.DataFrame(columns=[ "vector_size", "variant", "batch_size", "speedup", "throughput"])
   if batch_size is not None:
      filtered = dataframe[(dataframe["data_type"]==64) & (dataframe["column_count"] == 1) & (dataframe["batch_size"]==batch_size)]
   else:
      filtered = dataframe[(dataframe["data_type"]==64) & (dataframe["column_count"] == 1)]
   for index, row in filtered.iterrows():
      if row["vector_extension_name"] == "SSE" and row["query_count"] == 2:
         should_append = True
      elif row["vector_extension_name"] == "AVX2" and row["query_count"] == 4:
         should_append = True
      elif row["vector_extension_name"] == "AVX512" and row["query_count"] == 8:
         should_append = True
      else:
         should_append = False
      if should_append:
         df_varying_vector_sizes = df_varying_vector_sizes.append({
            "vector_size": vector_sizes[row["vector_extension_name"]],
            "variant": row["VariantPretty"],
            "batch_size": row["batch_size"],
            "throughput": row["Throughput"],
            "speedup": row["SpeedUp"]
         }, ignore_index=True)

   num_locations = len(df_varying_vector_sizes["vector_size"].unique())
   hatches_iterator = itertools.cycle(hatches)

   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g0 = sns.catplot(kind='bar', x='vector_size', y='speedup', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_vector_sizes, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g0 = sns.catplot(kind='bar', x='vector_size', y='speedup', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_vector_sizes, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      (g0).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g0.axes.flat] # remove the original texts
         # important to add this before setting titles
         g0.set_titles(row_template = '# Batch Size: {row_name}')
      g0.set(xlabel='Vector Size', ylabel='Workload-Speedup')
      plotno = 0
      for ax in g0.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         ax.axhline(1, ls='--')
         plotno +=1

   num_locations = len(df_varying_vector_sizes["vector_size"].unique())
   hatches_iterator = itertools.cycle(hatches)
   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g1 = sns.catplot(kind='bar', x='vector_size', y='throughput', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_vector_sizes, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g1 = sns.catplot(kind='bar', x='vector_size', y='throughput', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_vector_sizes, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      (g1).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g1.axes.flat] # remove the original texts
         # important to add this before setting titles
         g1.set_titles(row_template = '# Batch Size: {row_name}')
      g1.set(xlabel='Vector Size', ylabel='Throughput [GiB/s]')
      plotno = 0
      for ax in g1.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         plotno +=1
   return [g0, g1]

def create_figure_varying_column_sharing( dataframe, legend, batch_size=None ):
   df_varying_column_count = pd.DataFrame(columns=["column_count", "variant", "batch_size", "speedup", "throughput"])
   if batch_size is not None:
      filtered = dataframe[(dataframe["vector_extension_name"]=="AVX512") & (dataframe["data_type"] == 64) & (dataframe["batch_size"]==batch_size) & (dataframe["query_count"]==8)]
   else:
      filtered = dataframe[(dataframe["vector_extension_name"]=="AVX512") & (dataframe["data_type"] == 64) & (dataframe["query_count"]==8)]
   for index, row in filtered.iterrows():
      df_varying_column_count = df_varying_column_count.append({
         "column_count": row["column_count"],
         "variant": row["VariantPretty"],
         "batch_size": row["batch_size"],
         "throughput": row["Throughput"],
         "speedup": row["SpeedUp"]
      }, ignore_index=True)


   num_locations = len(df_varying_column_count["column_count"].unique())
   hatches_iterator = itertools.cycle(hatches)

   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g0 = sns.catplot(kind='bar', x='column_count', y='speedup', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_column_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g0 = sns.catplot(kind='bar', x='column_count', y='speedup', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_column_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")

      (g0).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g0.axes.flat] # remove the original texts
         # important to add this before setting titles
         g0.set_titles(row_template = '# Batch Size: {row_name}')
      g0.set(xlabel='Number of Columns', ylabel='Workload-Speedup')
      plotno = 0
      for ax in g0.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         ax.axhline(1, ls='--')
         plotno +=1

   num_locations = len(df_varying_column_count["column_count"].unique())
   hatches_iterator = itertools.cycle(hatches)
   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g1 = sns.catplot(kind='bar', x='column_count', y='throughput', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_column_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g1 = sns.catplot(kind='bar', x='column_count', y='throughput', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_column_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")

      (g1).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g0.axes.flat] # remove the original texts
         # important to add this before setting titles
         g1.set_titles(row_template = '# Batch Size: {row_name}')
      g1.set(xlabel='Number of Columns', ylabel='Throughput [GiB/s]')
      plotno = 0
      for ax in g1.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         plotno +=1
   return [g0,g1]

def create_figure_varying_query_sharing( dataframe, legend, batch_size=None ):
   df_varying_query_count = pd.DataFrame(columns=["query_count", "variant", "batch_size", "speedup", "throughput"])
   if batch_size is not None:
      filtered = dataframe[(dataframe["vector_extension_name"]=="AVX512") & (dataframe["data_type"] == 64) & (dataframe["batch_size"]==batch_size) & (dataframe["column_count"]==1)]
   else:
      filtered = dataframe[(dataframe["vector_extension_name"]=="AVX512") & (dataframe["data_type"] == 64) & (dataframe["column_count"]==1)]

   for index, row in filtered.iterrows():
      df_varying_query_count = df_varying_query_count.append({
         "query_count": int(row["query_count"]),
         "variant": row["VariantPretty"],
         "batch_size": row["batch_size"],
         "throughput": row["Throughput"],
         "speedup": row["SpeedUp"]
      }, ignore_index=True)

   num_locations = len(df_varying_query_count["query_count"].unique())
   hatches_iterator = itertools.cycle(hatches)

   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g0 = sns.catplot(kind='bar', x='query_count', y='speedup', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_query_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g0 = sns.catplot(kind='bar', x='query_count', y='speedup', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_query_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")

      (g0).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g0.axes.flat] # remove the original texts
         # important to add this before setting titles
         g0.set_titles(row_template = '# Batch Size: {row_name}')
      g0.set(xlabel='Number of Concurrent Queries', ylabel='Workload-Speedup')
      plotno = 0
      for ax in g0.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         ax.axhline(1, ls='--')
         plotno +=1

   hatches_iterator = itertools.cycle(hatches)
   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g1 = sns.catplot(kind='bar', x='query_count', y='throughput', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_query_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g1 = sns.catplot(kind='bar', x='query_count', y='throughput', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_query_count, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")

      (g1).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g1.axes.flat] # remove the original texts
         # important to add this before setting titles
         g1.set_titles(row_template = '# Batch Size: {row_name}')
      g1.set(xlabel='Number of Concurrent Queries', ylabel='Throughput [GiB/s]')
      plotno = 0
      for ax in g1.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         plotno +=1
   return [g0, g1]

def create_figure_varying_value_size( dataframe, legend, batch_size=None ):
   df_varying_value_size = pd.DataFrame(columns=["value_size", "variant", "batch_size", "throughput", "speedup"])
   if batch_size is not None:
      filtered = dataframe[(dataframe["vector_extension_name"]=="AVX512") & (dataframe["batch_size"]==batch_size) & (dataframe["column_count"]==1)]
   else:
      filtered = dataframe[(dataframe["vector_extension_name"]=="AVX512") & (dataframe["column_count"]==1)]

   for index, row in filtered.iterrows():
      if row["query_count"] == max(filtered[(filtered["data_type"] == row["data_type"])]["query_count"]):

         df_varying_value_size = df_varying_value_size.append({
            "value_size": "{}-bit".format(row["data_type"]),
            "variant": row["VariantPretty"],
            "batch_size": row["batch_size"],
            "throughput": row["Throughput"],
            "speedup": row["SpeedUp"]
         }, ignore_index=True)

   num_locations = len(df_varying_value_size["value_size"].unique())
   hatches_iterator = itertools.cycle(hatches)

   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g0 = sns.catplot(kind='bar', x='value_size', y='speedup', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_value_size, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g0 = sns.catplot(kind='bar', x='value_size', y='speedup', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_value_size, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")

      (g0).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g0.axes.flat] # remove the original texts
         # important to add this before setting titles
         g0.set_titles(row_template = '# Batch Size: {row_name}')
      g0.set(xlabel='Data Value Size', ylabel='Workload-Speedup')
      plotno = 0
      for ax in g0.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         ax.axhline(1, ls='--')
         plotno +=1

   hatches_iterator = itertools.cycle(hatches)

   with sns.plotting_context("paper", font_scale=1.5):
      if batch_size is not None:
         g1 = sns.catplot(kind='bar', x='value_size', y='throughput', hue='variant', palette=color_dict, hue_order=variant_order, data = df_varying_value_size, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")
      else:
         g1 = sns.catplot(kind='bar', x='value_size', y='throughput', hue='variant', palette=color_dict, row='batch_size', hue_order=variant_order, data = df_varying_value_size, legend_out=False, legend=legend, alpha=0.5, edgecolor=".1")

      (g1).despine(left=False, top=False, right=False, bottom=False)
      if batch_size is not None:
         [plt.setp(ax.texts, text="") for ax in g1.axes.flat] # remove the original texts
         # important to add this before setting titles
         g1.set_titles(row_template = '# Batch Size: {row_name}')
      g1.set(xlabel='Data Value Size', ylabel='Throughput [GiB/s]')
      plotno = 0
      for ax in g1.fig.get_axes():
         for i, bar in enumerate(ax.patches):
            if i % num_locations == 0:
               hatch = next(hatches_iterator)
            bar.set_hatch(hatch)
         ax.yaxis.set_major_locator(ticker.MultipleLocator(2))
         if legend and plotno == 0:
            ax.legend(title='', fontsize='x-small', frameon=False)
         plotno +=1
   return [g0,g1]

def create_overview(dataframe, base_path):
   figures = [
      { "fig": create_figure_varying_vector_sizes(dataframe, True), "fname": "{}/varying_vector_size".format(base_path) },
      { "fig": create_figure_varying_column_sharing(dataframe, False), "fname": "{}/varying_column_count".format(base_path) },
      { "fig": create_figure_varying_query_sharing(dataframe, False), "fname": "{}/varying_query_count".format(base_path) },
      { "fig": create_figure_varying_value_size(dataframe, False), "fname": "{}/varying_value_size".format(base_path) }
   ]
   fignames = []
   for fig in figures:
      fig["fig"][0].savefig("{}_tmp.png".format(fig["fname"]))
      fignames.append("{}_tmp.png".format(fig["fname"]))

   images = [Image.open(x) for x in fignames]
   widths, heights = zip(*(i.size for i in images))
   total_width = sum(widths)
   max_height = max(heights)
   new_im = Image.new('RGB', (total_width, max_height))

   x_offset = 0
   for im in images:
      new_im.paste(im, (x_offset,0))
      x_offset += im.size[0]
   new_im.save("{}/overview_speedup.png".format(base_path))
   for im in fignames:
      os.remove(im)

   fignames = []
   for fig in figures:
      fig["fig"][1].savefig("{}_tmp.png".format(fig["fname"]))
      fignames.append("{}_tmp.png".format(fig["fname"]))
   images = [Image.open(x) for x in fignames]
   widths, heights = zip(*(i.size for i in images))
   total_width = sum(widths)
   max_height = max(heights)
   new_im = Image.new('RGB', (total_width, max_height))

   x_offset = 0
   for im in images:
      new_im.paste(im, (x_offset,0))
      x_offset += im.size[0]
   new_im.save("{}/overview_throughput.png".format(base_path))
   for im in fignames:
      os.remove(im)



if len(sys.argv) != 3:
   print("Invalid number of arguments.")
   exit(1)

base_path=sys.argv[1]
file_name=os.path.splitext(sys.argv[2])[0]

out_path="{}/processed".format(base_path)
file_out_name="{}/processed_{}.csv".format(out_path, file_name)
file_in_name="{}/raw/{}.csv".format(base_path, file_name)

print(out_path)
print(file_in_name)

try:
   file = open(file_in_name, "r")
except IOError:
   print("Could not open")
df = pd.read_csv(file,
                 sep=';',     # field separator
                 comment='#', # comment
                 skipinitialspace=True,
                 skip_blank_lines=True,
                 error_bad_lines=False,
                 warn_bad_lines=True
                 ).sort_index()
df.fillna('no value', inplace=True)
print("Validating results...")
repetition_count = len(list(df["rep"].unique()))
tmp = df.groupby(
   [
      'vector_extension_name', 'data_type',
      'workload_processing_name', 'intermediate_format', 'build_variant_name',
      'column_count', 'query_count',
      'query_processing_variant_name', 'batch_size', 'result'
   ])['execution_time_ns'].describe()[['count']]
for index, row in tmp.iterrows():
   if row["count"] != repetition_count:
      print(row)
      raise Exception("Something went horribly wrong")
print("Everything ok.")

df = df.groupby(
   [
      'data_size', 'vector_extension_name', 'data_type',
      'workload_processing_name', 'intermediate_format', 'build_variant_name',
      'column_count', 'query_count',
      'query_processing_variant_name', 'batch_size'
   ])['execution_time_ns'].mean().reset_index()
baseline = df[(df["build_variant_name"]=="SEQ") & (df["intermediate_format"]=="BITMASK")]
#name_pretty = { "SEQUENTIAL": "Sequential Load", "GATHER": "Gather"}
colidx = []
throughput = []
data_size_pretty = []
slowdown = []
variant_pretty = []
speedup = []
for index, row in df.iterrows():
   bs_ns = float(baseline[
                    ( baseline["data_size"] == row["data_size"] ) &
                    ( baseline["vector_extension_name"] == row["vector_extension_name"] ) &
                    ( baseline["data_type"] == row["data_type"] ) &
                    ( baseline["column_count"] == row["column_count"]) &
                    ( baseline["query_count"] == row["query_count"]) &
                    ( baseline["query_processing_variant_name"] == row["query_processing_variant_name"]) &
                    ( baseline["batch_size"] == row["batch_size"])
                    ]["execution_time_ns"])
   if row["data_size"] < (1024*1024):
      data_size_pretty.append("{}KiB".format(int(row["data_size"]/1024)))
   elif row["data_size"] < (1024*1024*1024):
      data_size_pretty.append("{}MiB".format(int(row["data_size"]/(1024*1024))))

   if row["build_variant_name"] == "SEQ":
      variant_pretty.append("SISQ")
   else:
      variant_pretty.append("SIMQ-{}".format(row["build_variant_name"]))
   throughput.append(
      ( (  row["data_size"] / ( 1024 * 1024 * 1024 ) ) * ( row["query_count"] ) )/
      ( row["execution_time_ns"] / 1000000000 )
   )
   slowdown.append(row["execution_time_ns"]/bs_ns)
   speedup.append(bs_ns/row["execution_time_ns"])
   colidx.append(index)
kwargs = {"SlowDown": pd.Series(slowdown, index=colidx)}
df = df.assign(**kwargs)
kwargs = {"SpeedUp": pd.Series(speedup, index=colidx)}
df = df.assign(**kwargs)
kwargs = {"Throughput": pd.Series(throughput, index=colidx)}
df = df.assign(**kwargs)
kwargs = {"DatasizePretty": pd.Series(data_size_pretty, index=colidx)}
df = df.assign(**kwargs)
kwargs = {"VariantPretty": pd.Series(variant_pretty, index=colidx)}
df = df.assign(**kwargs)

df = df[(df["build_variant_name"]!="OFFLINE")]

df.to_csv(file_out_name, sep=";", index=False)

color_dict = {
   "SISQ": "#b3b3ff",
   "SIMQ-GATHER": "#ffb3b3",
   "SIMQ-BUFFER": "#ecd9c6",
   "SIMQ-SET": "#bcf6b1",
   "SIMQ-BROADCAST": "#808080"
   # "SISQ": "#808080",
   #"SIMQ-OFFLINE": "#ecd9c6",
   # "SIMQ-GATHER": "#b3b3ff",
   # "SIMQ-BUFFER": "#bcf6b1",
   # "SIMQ-SET": "#ffb3b3",
   # "SIMQ-BROADCAST": "#f6f2b1",
}
hatches = [ "" , "///" , "\\\\\\", "///\\\\\\", "ooo"]
variant_order = [
   "SISQ",
   #"SIMQ-OFFLINE",
   "SIMQ-GATHER",
   "SIMQ-BUFFER",
   "SIMQ-SET",
   "SIMQ-BROADCAST",
]
vector_sizes = { "SSE": 128, "AVX2": 256, "AVX512": 512 }

create_overview(df, out_path)

for batch_size in sorted(list(df["batch_size"].unique())):
   create_figure_varying_vector_sizes(df, True, batch_size)[0].savefig("{}/varying_vector_size_batchsize_{}.pdf".format(out_path, batch_size))
   create_figure_varying_column_sharing(df, False, batch_size)[0].savefig("{}/varying_column_count_batchsize_{}.pdf".format(out_path, batch_size))
   create_figure_varying_query_sharing(df, False, batch_size)[0].savefig("{}/varying_query_count_batchsize_{}.pdf".format(out_path, batch_size))
   create_figure_varying_value_size(df, False, batch_size)[0].savefig("{}/varying_value_size_batchsize_{}.pdf".format(out_path, batch_size))

print("Processed Data written to {}".format(out_path))
