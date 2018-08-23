# BGCPPChallenge


//Overview 

The objective of this project is to create XML files based on provided dummy data and validate against supplied XSD (Schema) file. Additionally, to export XML files to JSON files. 


Environment 

The program is written in C++ using various existing Library and was compiled in Docker (Ubuntu-container)  
•	TINYXML – to create XML files

•	XERCES-C++ -to validate XML files 

•	JSONCPP – to export XML files to JSON files

//Prerequisite

      Docker INSTALLATION 

Install Docker from this link (https://hub.docker.com/_/gcc/)

In command line Run docker --version and ensure that you have a supported version of Docker: 
Build the container if there is none  where  you wish to compile the source code and update with revelant library from the command line. 

docker ps      //  shows the list of container 

dokcer exec –it  container_name /bin/bash    // executes the  container container_name in ubuntu

 
After executing the container INSTALL relevant library as follows 

$ apt-get install apt-get install libtinyxml-dev

$ apt-get install apt-get install libxerces-c3-dev

$ apt-get install apt-get install  libjsoncpp-dev


//Compilation and execution of source code 

Copy the source code and XSD file to the container in the command line as follows:

      docker cp filename.cpp container_name:/filename.cpp
      
Run the updated container in Ubuntu  

       docker exec -it container_name /bin/bash 
       
Check the copied files in root as follow

     $  ls 
     
Compile the source code 

    $   g++ filename.cpp -o filename  -lxerces-c -ltinyxml  -ljsoncpp
    
 exeecute the source code 
 
    $ ./filename.cpp
    
The output shall ask for user input to perform selected task. 

