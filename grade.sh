#! /bin/bash
#
#  Warning:  modifying this script would very likely defeat the purpose of having
#            it supplied to you.
#
#  This script can be used to test and grade your solution for the MIPS assembly
#  parser assignment.  This is the script we will use to do that, so if your tar
#  file does not work for you with this script, it won't work for us either.
#  That would be unfortunate.
#
#  Invoke as:  ./grade.sh
#
#  Last modified:  11:45 Sept 14 2016
#
#  To use this test script:
#     - Untar the distributed testing tar file into a directory; that should
#       create the following directory structure:
#
#          ./grade.sh                  - this script file
#          ./repository/driver.c       - C source for the test driver
#          ./repository/ASMParser.h    - supplied C header file 
#          ./repository/ParseResult.h  - supplied C header file
#          ./repository/Generate.h     - declaration for test case generator
#          ./repository/Generate.o     - 64-bit CentOS binary for test case generator
#          ./repository/Grade.h        - declaration for grading function
#          ./repository/Grade.o        - 64-bit CentOS binary for grading function 
#
#       We will refer to the extraction directory as the test directory.
#     - Set execute permissions for grade.sh.
#     - Prepare the tar file you intend to submit and place it into the same
#       directory as grade.sh.
#     - Execute the command "./grade.sh <name of soln tar file>" and check the results.
#
#     grade.sh will create a subdirectory, ./build, unpack your submission tar file
#     into it, copy the files from ./repository into ./build, and execute the build
#     command:
#                 gcc -o c2 -std=c99 -Wall -ggdb3 *.c *.o
#
#     The script will then check for the existence of an executable, c2.  If there
#     is no such file, the script will exit with an error message.  Otherwise, the
#     script will move the executable c2 into the test directory, and execute it
#     to test and grade your solution, then repeat the same test under Valgrind.
#
#     Relevant results can be found in the following files:
#         
#        buildLog.txt       output from the build process
#        vgrindLog.txt      full output from Valgrind test
#        vgrind_issues.txt  summary of Valgrind results
#        prefix.txt         full report, including all of the logs above,
#                           where "prefix" is the first token of the name
#                           you gave your tar file
#
#  Exit codes:
#     0   -  normal execution; no major errors were detected
#     1   -  something is wrong with the repository directory
#     2   -  submitted tar file name not given on command line
#     3   -  file named on command line does not exist
#     4   -  file named on command line is not a tar file
#     5   -  ParseResult.c is missing from submitted tar file
#     6   -  ASMParser.c is missing from submitted tar file
#     7   -  build failed
#     8   -  permissions error with compiled executable
#     9   -  test driver did not generate expected files
#
# Configuration variables:
#
#   Names for directories:
repositoryDir="repository"
buildDir="build"

#   Names for log files created by this script:
buildLog="buildLog.txt"
testLog="testLog.txt"
resultsLog="C2Results.txt"

#   Name for the executable
exeName="c2"

#   Names for output files created by the test driver:
instructionLog="ASMInstructions.txt"
scoreResultsLog="Scores.txt"

#   Delimiter to separate sections of report file:
Separator="============================================================"

############################################# fn to check repository
#
repositoryOK() {
	
	fList=("driver.c" "ASMParser.h" "ParseResult.h" "Generate.h" "Generate.o" "Grading.h" "Grading.o")
	
	if [[ ! -d ./$repositoryDir ]]; then
	   echo "Repository directory does not exist!"
	   echo "Download a fresh copy of the tar file and try again."
	   return 1
	fi
	
	for fName in ${fList[@]}
	do
	   if [[ ! -e "./$repositoryDir/$fName" ]]; then
	      echo "$fName is not in the repository!"
	      echo "Download a fresh copy of the tar file and try again."
	      return 2
	   fi
	done
	return 0
}

############################################# fn to check for tar file
#                 param1:  name of file to be checked
isTar() {

   mimeType=`file -b --mime-type $1`
   [[ $mimeType == "application/x-tar" ]]
}

##################################### fn to extract token from file name
#                 param1: (possibly fully-qualified) name of file
#  Note:  in production use, the first part of the file name will be the
#         student's PID
#
getPID() { 

   fname=$1
   # strip off any leading path info
   fname=${fname##*/}
   # extract first token of file name
   spid=${fname%%.*}
}

############################################################ Build executable:

   # Check for valid repository subdirectory:
   repositoryOK
   if [[ ! $? -eq 0 ]]; then
      echo "The repository directory does not exit, or its contents are not valid."
      echo "Fix this error."
      exit 1
   fi
   
   # Check for name of student's tar file on command line:
   if [[ $# -eq 0 ]]; then
      echo "Please supply the name of your tar file on the command line."
      exit 2
   fi

   # Verify presence of named file
   tarFile="$1"
   if [ ! -e $tarFile ]; then
      echo "The file $tarFile does not exist."
      echo $Terminus >> $Log
      exit 3
   fi

   # Verify parameter is really a tar file
   isTar "$tarFile"
   if [[ ! $? -eq 0 ]]; then
      echo "The file $tarFile is not a valid tar file."
      exit 4
   fi
   
   # Extract first token of tar file name (student PID when we run this)
   getPID $tarFile
  
   # Create log file:
   echo "Executing grade.sh..." > $buildLog
   echo >> $buildLog
   
   # Create build directory and put files into it:
   echo "Creating build subdirectory" >> $buildLog
   echo >> $buildLog
   # Create build directory if needed; empty it if it already exists
   if [[ -d $buildDir ]]; then
      rm -Rf ./$buildDir/*
   else
      mkdir $buildDir
   fi
   
   # Extract student's tar file to the build directory
   echo "Extracting student's files to the build directory:" >> $buildLog
   tar xvf $tarFile -C ./$buildDir >> $buildLog
   echo >> $buildLog
   
   # Check for existence of mandatory files in submission:
   if [[ ! -e "./$buildDir/ParseResult.c" ]]; then
      echo "The required file ParseResult.c was not submitted." >> $buildLog
      exit 5
   fi
   if [[ ! -e "./$buildDir/ASMParser.c" ]]; then
      echo "The required file ASMParser.c was not submitted." >> $buildLog
      exit 6
   fi
   
   if [[ -e ./$buildDir/$exeName ]]; then
      echo "Removing file $exeName from the build directory." >> $buildLog
      rm -Rf ./$buildDir/$exeName
   fi
   
   # Copy the repository files into the build directory
   echo "Copying files from the repository to the build directory:" >> $buildLog
   cp ./$repositoryDir/* ./$buildDir
   echo `ls ./$repositoryDir` >> $buildLog
   echo "Note:  that may have overwritten files you submitted (but should not have)." >> $buildLog

   # Move to build directory
   cd ./$buildDir

   # Build the executable; save gcc output to log file
   echo "Invoking gcc..." >> $buildLog
   gcc -o $exeName -std=c99 -Wall -ggdb3 *.c *.o >> $buildLog 2>&1
   echo >> $buildLog

   # Verify existence of executable
   if [[ ! -e $exeName ]]; then
      echo "Build failed; the file driver does not exist" >> $buildLog
      echo $Separator >> $buildLog
      mv $buildLog $resultsLog
      exit 7
   fi
   if [[ ! -x $exeName ]]; then
      echo "Permissions error; the file driver is not executable" >> $buildLog
      echo $Separator >> $buildLog
      mv $buildLog $resultsLog
      exit 8
   fi
   echo "Build succeeded..." >> $buildLog
   
   # Move executable up to test directory and return there
   echo "Moving the executable $exeName to the test directory." >> $buildLog
   mv ./$exeName .. >> $buildLog
   cd .. >> $buildLog
   
   # Delimit this section of the report file:
   echo $Separator >> $buildLog

############################################################ Test

   # Initiate test Log
   echo "Executing the test driver..." > $testLog
   echo >> $testLog
   
   # Execute driver in random mode:
   ./$exeName $instructionLog $scoreResultsLog -rand >> $testLog
   
   # Verify existence of output files from driver:
   outputExists="yes"
   if [[ ! -e $instructionLog ]]; then
      echo "$instructionLog was not created." >> $testLog
      outputExists="no"
   fi
   if [[ ! -e $scoreResultsLog ]]; then
      echo "$scoreResultsLog was not created." >> $testLog
      outputExists="no"
   fi
   if [[ "$outputExists" == "no" ]]; then
      mv $testLog $resultsLog
      echo $Separator >> $resultsLog
      cat $buildLog >> $resultsLog
      exit 9
   fi
   
############################################################ Run valgrind check

   # run same tests on valgrind
   #   full valgrind output is in $vgrindLog
   #   extracted counts are in $vgrindIssues
   vgrindLog="vgrindLog.txt"
   echo "Running valgrind test..." >> $vgrindLog
   vgrindSwitches=" --leak-check=full --show-leak-kinds=all --log-file=$vgrindLog --track-origins=yes -v"
   scoreResultsLog2="ScoresValgrind.txt"
   valgrind $vgrindSwitches ./c2 $instructionLog $scoreResultsLog2
   
   # accumulate valgrind error counts
   if [[ -e $vgrindLog ]]; then
      vgrindIssues="vgrind_issues.txt"
      echo "Valgrind issues:" > $vgrindIssues
      grep "in use at exit" $vgrindLog >> $vgrindIssues
      grep "total heap usage" $vgrindLog >> $vgrindIssues
      grep "definitely lost" $vgrindLog >> $vgrindIssues
      echo "Invalid reads: `grep -c "Invalid read" $vgrindLog`" >> $vgrindIssues
      echo "Invalid writes: `grep -c "Invalid write" $vgrindLog`" >> $vgrindIssues
      echo "Uses of uninitialized values: `grep -c "uninitialised" $vgrindLog`" >> $vgrindIssues
   else
      echo "Error running Valgrind test." >> $testLog
   fi
   
############################################################ File report

   # Write score summary to start report
   echo "Scores from individual translations:" > $resultsLog
   grep -w "Test" $scoreResultsLog >> $resultsLog
   echo >> $resultsLog
   grep -w "Total" $scoreResultsLog >> $resultsLog
   echo $Separator >> $resultsLog
   
   # Write valgrind summary counts to report
   if [[ -e $vgrindIssues ]]; then
      cat $vgrindIssues >> $resultsLog
   else
      echo "Valgrind results summary is not available." >> $resultsLog
   fi
   echo $Separator >> $resultsLog
   
   # Append instruction file to report; the existence check is redundant
   if [[ -e $instructionLog ]]; then
      echo "Test instructions:" >> $resultsLog
      echo >> $resultsLog
      cat $instructionLog >> $resultsLog
      echo $Separator >> $resultsLog
   else
      echo "The file $instructionLog was not created." >> $resultsLog
   fi
   
   # Append grading details to report; the existence check is redundant
   if [[ -e $scoreResultsLog ]]; then
      echo "Grading details:" >> $resultsLog
      cat $scoreResultsLog >> $resultsLog
      echo $Separator >> $resultsLog
   else
      echo "The file $scoreResultsLog was not created." >> $resultsLog
   fi
   
   # Append test log to report:
   if [[ -e $testLog ]]; then
      echo "Output from executing test driver:" >> $resultsLog
      cat $testLog >> $resultsLog
   else
      echo "The file $testLog was not created." >> $resultsLog
   fi
   echo $Separator >> $resultsLog
  
   # Append valgrind log to report:
   if [[ -e $vgrindLog ]]; then
      cat $vgrindLog >> $resultsLog
   else
      echo "Detailed Valgrind output is not available." >> $resultsLog
   fi
   echo $Separator >> $resultsLog
   
   # Append build log to report:
   echo "Output from build process:" >> $resultsLog
   cat $buildLog >> $resultsLog
   
   # Rename final report using token from tar file name:
   mv $resultsLog "$spid.txt"

exit 0
