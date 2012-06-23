
  Redirect permanent /trac /
  # N.B. The /svn alias is a no-op. It exists only so that WSGI doesn't steal
  # POSTs to it. This is a side-effect of moving Trac from /trac to /
  Alias /svn           /usr/local/www/htdocs
  Alias /releases      /usr/local/www/htdocs/releases 
  Alias /snapshots     /usr/local/www/htdocs/snapshots
  Alias /chrome        /usr/local/www/trac/htdocs
  Alias /adminguide    /usr/local/www/htdocs/adminguide
  Alias /man-html      /usr/local/www/htdocs/man-html
  Alias /images        /usr/local/www/htdocs/images
  Alias /favicon.ico   /usr/local/www/htdocs/favicon.ico
  Alias /bbdoc.css     /usr/local/www/htdocs/bbdoc.css
  Alias /bbdoc-man.css /usr/local/www/htdocs/bbdoc-man.css
  Alias /robots.txt    /usr/local/www/htdocs/robots.txt
  Alias /googlede93e0b02a8808de.html /usr/local/www/htdocs/googlede93e0b02a8808de.html
  Alias /nortonsw_10631d70-e410-0.html /usr/local/www/htdocs/nortonsw_10631d70-e410-0.html

  Redirect permanent /accounts.html    /wiki/CertificatesAndAccountsManagement
  Redirect permanent /bbackupctl.html  /wiki/ControllingAClient
  Redirect permanent /client.html      /wiki/ConfiguringAClient
  Redirect permanent /comparison.html  /wiki/BoxComparison
  Redirect permanent /description.html /wiki/Overview
  Redirect permanent /install.html     /wiki/Installation
  Redirect permanent /license.html     /browser/box/trunk/LICENSE.txt
  Redirect permanent /nonroot.html     /wiki/RunningWithoutRoot
  Redirect permanent /openssl.html     /wiki/OpenSSLNotes
  Redirect permanent /restore.html     /wiki/VerifyAndRestoreBackups
  Redirect permanent /retrieve.html    /wiki/RetrievingFiles
  Redirect permanent /server.html      /wiki/ConfiguringAServer
  Redirect permanent /serverfix.html   /wiki/FixingCorruption
  Redirect permanent /space.html       /wiki/CheckingUsage
  Redirect permanent /trouble.html     /wiki/Troubleshooting
  #Redirect gone      /instguide
  Redirect gone      /004-005.html
  Redirect gone      /005-006.html
  Redirect gone      /006-007.html
  Redirect gone      /build

  <Directory "/usr/local/www/trac/htdocs">
    Order allow,deny
    Allow from all
  </Directory>

  # N.B. This must come after the aliases for static files
  WSGIScriptAlias / /usr/local/www/trac/cgi-bin/trac.wsgi

  <Directory /usr/local/www/trac/cgi-bin>
    WSGIProcessGroup bb-trac
    WSGIApplicationGroup %{GLOBAL}
    Order deny,allow
    Allow from all
  </Directory>

  <LocationMatch "^/(chrome|adminguide|man-html|images|favicon.ico|bbdoc.css)">
    SetHandler None
  </LocationMatch>

  <Directory /usr/local/www/htdocs/man-html>
      Options +Indexes
      IndexOptions +FancyIndexing
      IndexIgnore .
  </Directory>

  DAVLockDB /var/db/mod_dav/DAVLock
  <Location /svn>
      DAV svn
      SVNPath /data/svn
      AuthzSVNAccessFile /data/svn/conf/authz
      AuthUserFile /data/svn/conf/users
      AuthType Basic
      AuthName "Box Backup Dev"
      <LimitExcept GET PROPFIND OPTIONS REPORT>
          Require valid-user
      </LimitExcept>
  </Location>

