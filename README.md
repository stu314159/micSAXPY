Simple SAXPY code to test native mode MIC programming on Cray XC30 environment

module actions prior to compiling:
module swap PrgEnv-cray PrgEnv-intel
module swap craype-ivybridge craype-intel-knc
module unload cray-libsci

The jobscript gives some info on the environment data needed to run for batch submission.
