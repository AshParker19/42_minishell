# minitester
Output tester for the 42 Common Core 'minishell' project | Made to help during the development stages | On going

Prerequisites:
- Have 'expect' installed in your linux distribution. If not, run:
sudo apt install expect
- Your shell executable must have functional prompt capturing and processing capabilities
- Your shell must be named 'minishell' and have a readline prompt containing the sequence '$ ' (dollar sign + space)
- Your executable must be compiled without -fsanitize statements, as it would alter 'minitesters' results


Instructions:
- Place the 'minitester' folder next to your minishell executable
- Enter the 'minitester' folder and run:
bash ./minitester.sh


Evaluating the results:
- Check individual tests by comparing the output of the files within the 'out_bash' and 'out_minishell' folders.
For this, look for matching filenames in both folders in the format 'res + test number'
- Check the content of the performed test in the 'test_list' folder (test + test number + .sh)
- At the time of writing, this program has not been tested against final minishell projects.
Please, see this program as an auxiliar program and not as a means of final testing.


Further usage:
- You can add more tests by adding new lines to the "tests.txt" file within the 'minitester' folder.
  Please add them before the last line of the file (containing the 'exit\' sequence)
- New tests function properly in one-line format. At the time of writing multiline test format has not been addressed


Final considerations:
- In cases where results involve stderr messages, preference was given to expect's messaging system over bash's.
This was done, both due to expect's constraints, and to allow results to match up in diff statements whenever standard errors are involved.
This also means that you won't be able to compare your shell's own messaging system against the original bash when running 'minitester'.
- A validation was added to avoid failing scores in tests containing the character ';'.
This was done to avoid mismatching results, as the project guides state that this character is not to be interpreted by your minishell.
If needed, the same can be removed by deleting the 'elif' condition and corresponding statements in 'veridict.sh'.

Thanks!
