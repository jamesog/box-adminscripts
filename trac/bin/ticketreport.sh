#!/bin/sh

# Need to set PATH for cron
PATH=/bin:/usr/bin:/usr/local/bin

SQLFILE=/tmp/tktqry.$$
OUTFILE=/tmp/ticketreport.$$
MSG=/tmp/ticketmsg.$$
RECIPIENT=boxbackup-dev@boxbackup.org
FROM=trac@boxbackup.org

cat > $SQLFILE << __E
\pset border 0
SELECT 	substring(status from 1 for 1) AS "S",
	id AS "Ticket",
	owner AS "Owner",
	component AS "Component",
	substring(summary from 1 for 60) AS "Summary"
FROM ticket WHERE status = 'new' OR status = 'assigned'
ORDER BY id,component;
__E

cat >> $MSG << __MSG
From: $FROM
To: $RECIPIENT
Subject: Current open tickets

Note: to view an indiviual ticket, use:
  https://www.boxbackup.org/trac/ticket/(number)

The following is a listing of current problems submitted by Box Backup users.
These represent problem reports covering all versions including
experimental development code and obsolete releases.


__MSG

psql -h localhost -d trac-boxbackup -U trac -f $SQLFILE -o $OUTFILE > /dev/null

sed -e 's/(\([[:digit:]]*\) rows)/\1 tickets total./g' -i "" $OUTFILE

cat $OUTFILE >> $MSG

/usr/sbin/sendmail -t < $MSG

rm $SQLFILE
rm $OUTFILE
rm $MSG
