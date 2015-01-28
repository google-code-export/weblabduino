package com.example.weblab;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;


public class ConexaoMysql {
   // JDBC driver name and database URL
   static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
   static final String DB_URL = "jdbc:mysql://192.168.42.1/experimentos";

   //  Database credentials
   static final String USER = "experimentos";
   static final String PASS = "p=r*i2";
     
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
                       
      String[] valores = dados.split("-");

      sql = "INSERT INTO `cna`(`data`, `ch0`, `ch1`) VALUES (CURRENT_TIMESTAMP,"+valores[0]+","+valores[1]+");";
     
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
