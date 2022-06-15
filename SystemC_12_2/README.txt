This is the README file for:

        SystemC Fundamentals - version 12.2 revision 19.09

The software products and versions required for this course are:

        x300 Xcelium Single-Core 19.09.001-s (or later)

The author tested the lab data with *only* that installation and the platform:
        Linux RH EE 6.5

The author tested the lab data with *only* the bundled GNU compiler.

Before you run any Cadence software, verify your patch level and install
any missing required patches. Enter:
        checkSysConf XCELIUM19.09

If you intend to directly invoke the GCC compiler in the Cadence installation,
you must read and comply with configuration requirements described in:

Document : Installation and Configuration Information, Product Version 19.09
  Chapter  : Configuring the Simulator
    Section  : Xcelium Simulators
    Subsection : SystemC Simulation Configuration Requirements

Document   : SystemC Simulation User Guide, Product Version 19.09
  Chapter    : Simulating SystemC Models
    Section    : Checking Your Environment Configuration
      Subsection : Environment Checks
    Section    : Compiling SystemC Models with xmsc
      Subsection : Simulating SystemC Designs Using Dynamic Linking

You should then verify your XM-SC simulator environment using the
"xmsc_env_check" utility (use whatever switches apply):
  xmsc_env_check [-64bit] [-gnu] [-manual] [-static]
The xmsc_env_check utility by default verifies only the 32-bit native compiler
building a shared-object library under control of either the Makefiles or the
xmsc_run utility. You should include whatever options you need to test the
environment the way you intend to use it.

After installing the course lab data:
1 Modify the class_setup C-shell script as needed for your platform and shell.
   This shell script sets the path variables to find executables and libraries.
2 Source the class_setup shell script.
   You must source this script in every shell in which you run the tools.
3 Test the database with the C-shell script ".testscript".
   The test script tests only for a simulator license.

In the lab directory hierarchy:
  ./sources contains unmodified lab sources for rebuilding labs the students
    have unrecoverably broken. Do not run anything in a sources directory!
  ./solutions contains completed versions of work a student would do, but not
    copies of unmodified sources. Do not run anything in a solutions directory!

The top level lab directory (SystemC_12_2) contains hidden shell scripts.
You run these scripts from the top level lab directory.
You can modify these scripts to loop through the labs you want.
Do the labs in order as subsequent labs may rely upon previous lab results.
  .make_new.sh  -- Makes new labs by copying from ./sources
  .make_do.sh   -- Does the labs much as the students would do

Each lab in the ./sources directory also contains hidden shell scripts.
You run these scripts FROM THE LAB DIRECTORY (lab*).
Do not run or edit anything in the ./sources or ./solutions hierarchies!
  .make_new.sh  -- Makes lab new by copying from ../sources
  .make_do.sh   -- Does the lab much as the student would do
 
