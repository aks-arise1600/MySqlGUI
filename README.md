![alt text](https://github.com/anil-arise1600/MySqlGUI/blob/main/images/mysql-gui.png?raw=true)

# MySQL GUI

MySQL GUI is a UI based MySQL workbench.



## Install Dependencies 

		sudo apt update
		sudo apt install -y build-essential qt5-qmake qtbase5-dev qtbase5-dev-tools cmake git
		sudo apt install -y mysql-server libmysqlclient-dev
		sudo systemctl start mysql.service
		
## Configure MySQL (root password)

		sudo mysql
		
		ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'password';
		exit


## Build with cmake

		git clone https://github.com/anil-arise1600/MySqlGUI.git
		cd MySqlGUI
		mkdir cBuild && cd cBuild
		cmake ..
		make
	
## Build with qmake

		git clone https://github.com/anil-arise1600/MySqlGUI.git
		cd MySqlGUI
		mkdir qBuild && cd qBuild
		qmake ..
		make
	
	
	
## MySQL Connection

![alt text](https://github.com/anil-arise1600/MySqlGUI/blob/main/docs/Screenshots/MySQLGUI_001.png?raw=true)


## Select Query on selection treeview item

![alt text](https://github.com/anil-arise1600/MySqlGUI/blob/main/docs/Screenshots/MySQLGUI_002.png?raw=true)


## Insert Values on selected treeview item with right click

![alt text](https://github.com/anil-arise1600/MySqlGUI/blob/main/docs/Screenshots/MySQLGUI_003.png?raw=true)

![alt text](https://github.com/anil-arise1600/MySqlGUI/blob/main/docs/Screenshots/MySQLGUI_004.png?raw=true)

	
## References
1. [MySQL Install](https://www.digitalocean.com/community/tutorials/how-to-install-mysql-on-ubuntu-20-04)
2. [MySQL Queries](https://www.mysqltutorial.org/mysql-cheat-sheet.aspx)
3. [Qt SQLDatabase programming](https://doc.qt.io/qt-6/qsqldatabase.html)




