#!/usr/bin/env python

# this function sets up the command-line interface for the command
def usage(cmdline):
  cmdline.set_author('W. Heath Robinson (h.robinson@implausible.com)')
  cmdline.set_synopsis('Compute voxel-wise geometric mean across volumes')
  # command arguments and options
  cmdline.add_argument('input', help='an input image')
  cmdline.add_argument('output', help='the output image')
  cmdline.add_argument('-invalid', help='value if any intensity is non-positive (default = NaN)')
  # optional citation and non-default copyright statement
  cmdline.add_citation('Robinson, W.H. A treatise on geometric averaging. Contrived Science Weekly, 2019.')
  cmdline.set_copyright('Copyright (c) 2019 Heath Robinson Labs.')


# this function contains the primary operation of the command
def execute():
  from mrtrix3 import app, path, run
  # import data in temporary directory
  app.activate_scratch_dir()
  # use f-strings to support user-specified paths that may contain spaces
  # typically import user-specified data into the scratch directory before processing
  # have to set "preserve_pipes=True" in case input image is piped from another MRtrix3 command;
  #   it can't be deleted until the command is completed
  run.command(f'mrconvert {app.ARGS.input} in.mif -strides 0,0,0,1',
              preserve_pipes=True)
  # primary command processing
  run.command('mrcalc in.mif -log log.mif')
  run.command('mrmath -axis 3 log.mif mean meanlog.mif')
  if app.ARGS.invalid is not None:
    run.command(f'mrcalc meanlog.mif -exp NaN {app.ARGS.invalid} -replace out.mif')
  else:
    run.command('mrcalc meanlog.mif -exp out.mif')
  # copy to output
  # "mrconvert_keyval" with input image ensures accurate "command_history" in output header
  # must honour if user specifies -force
  # "preserve_pipes=True" necessary to make sure if output image is a pipe it doesn't get deleted
  run.command(f'mrconvert out.mif {app.ARGS.output}',
              mrconvert_keyval=app.ARGS.input,
              force=app.FORCE_OVERWRITE,
              preserve_pipes=True)

