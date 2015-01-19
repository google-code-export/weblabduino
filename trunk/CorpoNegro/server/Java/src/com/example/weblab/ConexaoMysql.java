package com.example.weblab;

import java.sql.*;

public class ConexaoMysql {
   // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://localhost/experimentos";

   //  Database credentials
   static final String USER = "cna";
   static final String PASS = "cna";
   char[] dadosArduinoDB;
      
   public void EnviarDadosDB(String dados) {
   Connection conn = null;
   Statement stmt = null;
   
   
   try{
      //STEP 2: Register JDBC driver
      Class.forName("com.mysql.jdbc.Driver");

      //STEP 3: Open a connection
      System.out.println("Connecting to database...");
      conn = DriverManager.getConnection(DB_URL,USER,PASS);

      //STEP 4: Execute a query
      System.out.println("Creating statement...");
      stmt = conn.createStatement();
      String sql;
    		  
      char[] dadosArduino = dados.toCharArray();
      dadosArduinoDB = null;
      
      for (int i = 21; i < 21; i++){
    	  
    	  if(dadosArduino[i]==';'){
    		 dadosArduinoDB[i]=dadosArduino[i++];
    	  }

      }
      
      sql = "INSERT INTO `cna`(`ch0`"
      		+ ", `ch1`"
      		+ ", `ch2`"
      		+ ", `ch3`"
      		+ ", `ch4`"
      		+ ", `ch5`"
      		+ ", `ch6`"
      		+ ", `ch7`"
      		+ ", `ch8`"
      		+ ", `ch9`"
      		+ ", `ch10`"
      		+ ", `ch11`"
      		+ ", `ch12`"
      		+ ", `ch13`"
      		+ ", `ch14`"
      		+ ", `ch15`"
      		+ ", `ch16`"
      		+ ", `ch17`"
      		+ ", `ch18`"
      		+ ", `ch19`"
      		+ ", `data`) "
      		+ "VALUES (1"
			+",2"
			+",2"
			+",3"
			+",4"
			+",5"
			+",0"
			+",1"
			+",2"
			+",3"
			+",4"
			+",5"
			+",6"
			+",7"
			+",8"
			+",9"
			+",10"
			+",11"
			+",12"
			+",13"
      		+ ",CURRENT_TIMESTAMP);";
      
      stmt.executeUpdate(sql);
      
      //STEP 6: Clean-up environment
      stmt.close();
      conn.close();
   }catch(SQLException se){
      //Handle errors for JDBC
      se.printStackTrace();
   }catch(Exception e){
      //Handle errors for Class.forName
      e.printStackTrace();
   }finally{
      //finally block used to close resources
      try{
         if(stmt!=null)
            stmt.close();
      }catch(SQLException se2){
      }// nothing we can do
      try{
         if(conn!=null)
            conn.close();
      }catch(SQLException se){
         se.printStackTrace();
      }//end finally try
   }//end try
   System.out.println("Goodbye!");
}//end main
}//end FirstExample