#!/bin/sh

export PATH=$PATH:/usr/local/bin
cd ~/trunk
svn update
cd documentation/boxbackup
make clean docs
/usr/local/bin/rsync box-html/ /usr/local/www/htdocs
