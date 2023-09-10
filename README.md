# Operating_systems

Name: Devansh Lingamaneni

Roll No: CS21B2023

**Linux/Unix Commands used**

**1. Directory Operations**
   - `ls`: List files and directories in the current directory.
   - `ls -l`: List files and directories in long format, including permissions, owner, group, size, and modification time.

**2. File Operations**
   - `cat`: Print the contents of a file to the screen.
   - `more`: Display the contents of a file one page at a time.
   - `less`: Display the contents of a file one page at a time, with the ability to move forward and backward in the file.

**3. File Manipulation**
   - `touch`: Create an empty file with the specified name or update the timestamp of an existing file.
   - `cp`: Copy files or directories from one location to another.
   - `cp -R`: Recursively copy directories and their contents from one location to another.
   - `rm`: Remove (delete) files or directories permanently.
   - `mkdir`: Create a new directory with the specified name.

**4. Archive and Compression**
   - `tar`: Archive files together into a single file (tape archive) or extract files from a tar archive.
     - `tar czvf`: Create a new tar archive, compress it using gzip, and specify the filename of the new archive.
     - `tar xvf`: Extract files from a tar archive and specify the filename of the archive to extract from.
   - `gzip`: Compress files using the gzip compression algorithm.
     - `gzip -d`: Decompress files that were compressed using gzip.

**5. Process Management**
   - `ps`: Display a snapshot of the current processes running on the system.
     - `ps aux`: Display detailed information about all processes running on the system.
   - `top`: Display a real-time dynamic view of running processes and system information.
   - `pgrep`: List process IDs (PIDs) of processes that match specified criteria.
   - `pkill`: Terminate or signal processes based on their names or attributes.

**6. Secure Shell (SSH) and Networking**
   - `ssh`: Securely connect to a remote server using the SSH (Secure Shell) protocol.
     - `ssh -p <port> <username>@<address> -i <keyfile.pem>`: Securely connect to a remote server with specified options.

**7. File Comparison and Sorting**
   - `diff`: Compare and display the differences between two files line by line.
   - `sort`: Sort lines of text in ascending order or numerically.
     - `sort --numeric-sort`: Sort lines of text in ascending order numerically.

**8. System Information and Memory**
   - `pwd`: Print the working directory.
   - `free`: Display the amount of free and used memory (RAM) on the system.
     - `free -g | m | h`: Display memory sizes in gigabytes, megabytes, or human-readable format.

**9. Changing Permissions**
   - `chmod`: Change the permissions of a file or directory.
     - `chmod go+w`: Set write permission for the group and others on a file or directory.
     - `chmod o=wx`: Set execute (search) permission for others on a file or directory and remove write permission for others.
     - `chmod u-rw`: Remove read and write permissions for the owner of a file or directory.
     - `chmod +x`: Add execute (search) permission for the owner, group, and others on a file or directory.
