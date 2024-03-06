# 42 pipex

### Task
Write a C program that recreates the piping functionality of a shell. The following features should be implemented:

1. **Numerous commands:**
   
    `< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2` --> `./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2`

2. **heredoc functionality:**

    `cmd1 << LIMITER | cmd2 >> file` -->  `./pipex here_doc LIMITER cmd1 cmd2 file`


> **ATTENTION:** If you use a command with flags, enclose it in quotation marks (./pipex infile "cat -e" "cat -e" outfile)

### Utilization

```
git clone git@github.com:michmos/42_pipex.git && cd 42_pipex
make
```

### Examples
```
./pipex input_file "cat -e" "cat -e" "cat -e" "cat -e" output_file
./pipex input_file "ls -l -a" "cat -e -n" output_file
./pipex input_file "ls -l -a -f" "cat -e -n" output_file
./pipex here_doc "EOF" "cat -e" "wc -l" output_file
```
> The input file needs to be created before running the commands

### Tester
I also wrote a bash tester that compares the behaviour of the program with the actual shell piping. You can find it here:
![pipex tester](https://github.com/michmos/42_pipex_tester)
