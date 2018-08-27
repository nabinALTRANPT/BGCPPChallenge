# BGCPPChallenge


//Overview 

The objective of this project is to create XML files based on provided dummy data and validate against supplied XSD (Schema) file. Additionally, to export XML files to JSON files. 


Environment 

The program is written in C++ using various existing Library and was compiled in Docker (Ubuntu-container)  

//Prerequisite

  Docker INSTALLATION 

 Install docker with images and containers that allows cpp development  (https://hub.docker.com/_/gcc/)

 In command line Run docker --version and ensure that you have a supported version of Docker: 
  
      docker --version 

Build the container if there is none  where  you wish to compile the source code and update with revelant library from the command line with these steps. 

       docker run -it ubuntu bash  //  run an Ubuntu container 
       
       $ apt-get update  // update the container 
       
       $ apt-get install gcc   //   install gcc 
    
       docker ps      //  shows the list of container 

       dockcer exec –it  container_name /bin/bash    // executes the  container container_name in ubuntu

Libraries used: 

•	TINYXML – to create XML files

•	XERCES-C++ -to validate XML files 

•	JSONCPP – to export XML files to JSON files
 
After executing the container update the container and INSTALL relevant library as follows:

     $  apt-get update 

     $  apt-get install libtinyxml-dev

     $  apt-get install libxerces-c3-dev

     $  apt-get install  libjsoncpp-dev


//Compilation and execution of source code 

Copy the source code and XSD file to the container in the command line as follows:

      docker cp d.xsd container_name:/d.xsd
      
      docker cp final.cpp container_name:/final.cpp
 
 
Run the updated container in Ubuntu  

       docker exec -it container_name /bin/bash 
       
Check the copied files in root as follow

       $  ls 
     
Compile the source code 

      $   g++ final.cpp -o final  -lxerces-c -ltinyxml  -ljsoncpp
    
 exeecute the source code 
 
      $ ./final
    
The output shall ask for user input to perform selected task. 

