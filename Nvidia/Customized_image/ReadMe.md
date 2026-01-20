# Standard image file packaging steps

## 1. Create your own application within a standard image file.
## 2. Execute the packaging command on the system desktop.
	$ sudo tar -cvpzf backup.tar.gz --exclude=/backup.tar.gz --one-file-system / 
