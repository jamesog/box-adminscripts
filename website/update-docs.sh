#!/bin/sh

export PATH=$PATH:/usr/local/bin
cd ~/trunk
svn update
cd docs
make clean docs
/usr/local/bin/rsync -rv htmlguide/ /usr/local/www/htdocs
