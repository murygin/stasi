WHAT IT IS:
-----------
stasi is a browser based time reporting tool writte in php. Its purpose is
to collect the working hours of your colleagues that potentially worked on
different projects in potentially different branch offices. One can create
tasks assignable to projects, and summarize the total of projects. It comes
with user management.
It is based on software originally written by Daniel Murygin (formally known
as Daniel Schmidt) <daniel.murygin@gmail.com>  for Fork Unstable Media
(http://fork.de). It now is an OpenSource project covered by the BSD License
(see file "License" in this directory).

The name comes from a joke about big bad companies lurking all the time and
wanting to know every move of their lazy employes. Like the
Staatssicherheitsdienst (Stasi - https://en.wikipedia.org/wiki/Stasi) in the
former Deutsche Demokratische Republik.



OBTAINING:
----------

git clone https://github.com/murygin/stasi.git

INSTALLATION:
-------------

Required before Install:

* php4.X
* Mysql server
* Optionally cron and any MTA

Installation:

* Untar stasi-$version.tar.gz somewhere outside your webroot.
* Let a Vhost point to /path/to/stasi/htdocs.
* Add the following directive to your httpd.conf file:
```
<Directory /path/to/stasi/htdocs>
AllowOverride AuthConfig
php_value include_path /path/to/stasi/lib
</Directory>
```
* Create a database named 'zeit' for stasi:
```
  mysqladmin -u root -p*** create zeit
```
* Execute the database build script:
```
mysql -u root -p*** < scripts/zeit.sql
```
* Edit lib/config.inc to reflect your systems settings.
* Optionally edit scripts/reminder.sh and symlink to /etc/cron.daily/reminder.sh.
* Log on to stasi with u:Admin p:Admin.
* Go to kennwort and change the default password.
* Add users, projects, tasks as you wish. A new user is given the username as temporary password. Encourage new users to change the default password.

VERSION HISTORY:
----------------

*Version 1.0.1b2*
27.03.2002
* cleaned some more
* added Logout

*Version 1.0.1b*
26.03.2002
* Version number generated. 1.x was chosen because stasi was in mature state before versioning.
* Wrote Readme
* Rewrote zeit.sql
* Wrote reminder.sh
* cleaned up & secured db settings
