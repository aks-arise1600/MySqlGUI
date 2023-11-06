# MySQL GUI

MySQL UI based workbench 



## Install Dependencies 

		sudo apt update
		sudo apt install mysql-server libmysqlclient-dev
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
	

