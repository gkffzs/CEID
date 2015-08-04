#### (23Y538) - Internet Technologies [:link:](https://www.ceid.upatras.gr/en/undergraduate/courses/23%CE%A5538)

This repository contains the course assignment for the academic period of 2011-2012, done by
[George Kaffezas](https://github.com/gkffzs), [Aris Magripis](https://github.com/aris-mag) and Tasos Siaflekis. It is a
complete web system for image sharing, as described in `assignment.pdf`, developed from scratch. It follows the
three-tier architecture (data, logic and presentation layer) and has all the functionalities that were specified in the
assignment. The source code is included in `/www-folder`, and more information are to be found in `report.pdf`
(in Greek).

In order to test how the site works, and assuming you work on a
[Microsoft Windows](https://www.microsoft.com/el-gr/windows/) computer with internet access, you could follow these
instructions:
- Install [WampServer](http://www.wampserver.com/en/), in order to have a virtual server with PHP, MySQL, etc.
- Create a new database and the respective tables, as they're described in `/db_diagrams`.
- Copy the files of `/www-folder` into a new folder (i.e. `/ekona`) in the `/www` directory of your server.
- Configure your server along with the config files in `/database_layer/db_config.php`.
- Create three new folders, `/tmp` and `/users_album` in the site folder in `/www` directory, and `/private_images` in the parent directory of `/www` (probably in your `C:/` directory).
- Open your internet browser and navigate to `localhost/[name_of_the_folder]/presentation_layer/index.php`, to see the home page of the website.
