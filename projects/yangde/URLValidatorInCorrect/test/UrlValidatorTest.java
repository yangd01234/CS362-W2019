/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;

// Added



/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {


	   public UrlValidatorTest(String testName) {
	      super(testName);
	   }

	   
	   
	   public void testManualTest()
	   {
	//You can use this function to implement your manual testing	 
		   System.out.println("START OF MANUAL TESTING");
		   UrlValidator urlvalidator = new UrlValidator();
		   


		   assertNoExit("Validating null url", "false", urlvalidator, null);
		   assertNoExit("Validating shortest url", "true", urlvalidator, "http://0.com");
		   
		   // Testing SCHEME: per apache commons documentation, it will validate http, https, and ftp
		
		   assertNoExit("Validating http", "true", urlvalidator, "http://www.test.com/");
		
		   assertNoExit("Validating https", "true", urlvalidator, "https://www.test.com/");
		
		   assertNoExit("Validating ftp", "true", urlvalidator, "ftp://www.test.com/");
		
		   assertNoExit("Validating 00 prefix", "false", urlvalidator, "00://www.test.com/");
		   assertNoExit("Validating 0a prefix", "false", urlvalidator, "0a://www.test.com/");
		   
	   }
	   
	   
	   public void testYourFirstPartition()
	   {
		 
		 //You can use this function to implement your First Partition testing	   

	   }
	   
	   public void testYourSecondPartition(){
			 //You can use this function to implement your Second Partition testing	   

	
	   }
	   //You need to create more test cases for your Partitions if you need to 
	   
	   public void assertNoExit( String message, String expected, UrlValidator urlval, String url) {
		  String resultStr, result;
		   if(urlval.isValid(url)) {
			  resultStr = "["+message+"] "+"Expected: " + expected + " : true";
			  result = "true";
		  } else {
			  resultStr = "["+message+"] "+"Expected: " + expected + " : false";
			  result = "false";
		  }
		  
		  
		  if(expected == result) {
			  System.out.println("PASS - "+resultStr);
		  } else {
			  System.out.println("FAIL - "+resultStr);
			  
			  //COMMENT OUT THIS ASSERT IF YOU WANT CONTINUOUS TESTING
			  //assertTrue(expected == result);
		  }
		  
	   }
	   
	   /* Unit Test
	    * Start with smallest unit of url then expand
	    * Scheme + Path
	    * ex: news:comp.infosystems.www.servers.unix
	    * 
	    * Scheme + Authority + Path
	    * ex: telnet://192.0.2.16:80/
	    * 
	    * Scheme + Authority + Path + Query	
	    * 
	    * Scheme + Authority + Path + Query + Fragment
	    * 
	    * Scheme + Authority+ Port
	    */
	   
	   /*Unit testing for Scheme
	    * Params: 
	    * scheme[](String) - Array of schemes
	    * result(String)   - value of true or false
	    * urlval(UrlValidator object)
	    */
	   public void utScheme(String scheme[], String result, UrlValidator urlval) {
		   int i;
		   
		   for(i = 0; i<scheme.length; i++) {
			   String url = scheme[i]+"google.com";
			   assertNoExit(url, result, urlval, url);
		   }
	   }
	   
	   /* Host data
	    * max of 253 ASCII characters
	    * can contain A-Z, 0-9, and -
	    * must be deliminated by .  ex: en.wiki.org
	    * 
	    */
	   public void utHost(String host[], String result, UrlValidator urlval) {
		   int i;
		   
		   for(i = 0; i<host.length; i++) {
			   String url = "http://"+host[i];
			   assertNoExit(url, result, urlval, url);
		   }
	   }
	   
	   /* Testing Port
	   * make port int 0, 65535, and 70000, 1000000
	   * make sure port starts with :
	   */
	   
	   public void utPort(String result, UrlValidator urlval, int max) {
		   int host;
		   
		   String url = "http://www.google.com:";
		   
		   for (host = 0; host < max+1; host++) {
			   String hostUrl = url+host;
			   if(!(urlval.isValid(hostUrl))) {	   
				   if(result == "false") {
					   System.out.printf("PASS - ");
				   } else {
					   System.out.printf("FAIL - ");
					 //COMMENT OUT THIS ASSERT IF YOU WANT CONTINUOUS TESTING
					   //assertTrue(result == "false");
				   }
				   System.out.println("Invalid port at: "+hostUrl);
				   return;
			   }
		   }
		   System.out.println("PASS - Valid hosts from http://www.google.com:0 - 65535");
		   ;
	   }
	   
	   
	   
	   public void utPath(String path[], String result, UrlValidator urlval) {
		   int i;
		   
		   for(i = 0; i<path.length; i++) {
			   String url = "http://www.google.com"+path[i];
			   assertNoExit(url, result, urlval, url);
		   }
	   }
	   
	   
	   public void utQuery(String query[], String result, UrlValidator urlval) {
		   int i;
		   
		   for(i = 0; i<query.length; i++) {
			   String url = "http://www.google.com/testpath/"+query[i];
			   assertNoExit(url, result, urlval, url);
		   }
	   }
	   
	   public void utFragment(String fragment[], String result, UrlValidator urlval) {
		   int i;
		   
		   for(i = 0; i<fragment.length; i++) {
			   String url = "http://www.google.com/testpath/?=testquery"+fragment[i];
			   assertNoExit(url, result, urlval, url);
		   }
	   }
	   
	   public void testIsValid()
	   {
		   System.out.println("START OF UNIT TESTING");
		   //You can use this function for programming based testing
		   UrlValidator urlvalidator = new UrlValidator();

		   
		   /* Cited: rfc3986 documentation
		    * https://tools.ietf.org/html/rfc3986
		    * example: https://john.doe@www.example.com:123/forum/questions/?tag=networking&order=newest#top
		    * 
		    * scheme: https, http, ftp 
		    * host: www.example.com
		    * port: 123
		    * path: /forum/questions/
		    * query: ?tag=networking&order=newest
		    * fragment: #top
		    */
		   
		   /* Scheme data
		    * https, http, ftp
		    */
		   //TEST URLValidator - tolowercase/touppercase
		   //TEST if scheme is file, then it should work
		   
		   //TESTING SCHEME
		   String validScheme[] = {"http://", "https://", "ftp://", "hTtp://", "fTp://"};  
		   String invalidScheme[] = {"http", "httpssdf://", "0ftp://", "00://", "file://"};
		   
		   
		   System.out.println("==Unit Testing - valid scheme==");
		   utScheme(validScheme, "true", urlvalidator);
		   System.out.println("==Unit Testing - invalid scheme==");
		   utScheme(invalidScheme, "false", urlvalidator);
		   
		   
		   //TESTING HOST
		   String validHost[] = {"www.google.com", "www.a1-0.org", "www.a.net", "www.0.com", "www.a-a.com",
				   "www.ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg.com"}; //71 chars
		   String invalidHost[] = {"a//a.a-b.com", "w:ww.a1- 0.org", "ww__w.a.net", "w**ww.0.com", "w??ww.a-a.com",
				   "www.ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"
				   + "ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"
				   + "ggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg"
				   +".com"};
		   System.out.println("==Unit Testing - valid host==");
		   utHost(validHost, "true", urlvalidator);
		   System.out.println("==Unit Testing - invalid host==");
		   utHost(invalidHost, "false", urlvalidator);
		   
		   

		   //TESTING PORT
		   System.out.println("==Unit Testing - valid ports 0-65535==");
		   utPort("true", urlvalidator, 65535);
		   
		   System.out.println("==Unit Testing - invalid port 65536+==");
		   utPort("false", urlvalidator, 70000);
		   
		   /* path data
		    * beings with / or empty
		    * begins with / but not //
		    */
		   String validPath[] = {"/test/test", "/01test/ntest", "/alsoworks/works/works", "/wrap/", "", "/"};
		   String invalidPath[] = {"//notvalid", "/////////", "/ df"};
		   System.out.println("==Unit Testing - valid paths==");
		   utPath(validPath, "true", urlvalidator);
		   System.out.println("==Unit Testing - invalid paths==");
		   utPath(invalidPath, "false", urlvalidator);
		   
		   
		   /* query data
		    * starts with a ?
		    * can be alphanumeric
		    */
		   String validQuery[] = {"?test=5", "?55=66", "?ab=12", "?12=ab", "?1=0"};
		   String invalidQuery[] = {"? test5=1", "?test*= /5/5/", " ?t/e/s/t_=fd"};
		   System.out.println("==Unit Testing - valid queries==");
		   utQuery(validQuery, "true", urlvalidator);
		   System.out.println("==Unit Testing - invalid queries==");
		   utQuery(invalidQuery, "false", urlvalidator);
		   
		   /*
		    * fragment data
		    * starts with a #
		    */
		   String validFragment[] = {"#fragment1", "#fragment-1", "#01", "#aa"};
		   String invalidFragment[] = {"#^test1", "#|||||", "#extr aspace "};
		   System.out.println("==Unit Testing - valid fragments==");
		   utQuery(validFragment, "true", urlvalidator);
		   
		   urlvalidator = new UrlValidator(null, null, urlvalidator.NO_FRAGMENTS);
		   System.out.println("==Unit Testing - no fragments==");
		   utQuery(invalidFragment, "false", urlvalidator);
		   
		   
		   
		   
		   
		   // regex testing
		   // correct PATH_REGEX = "^(/[-\\w:@&?=+,.!/~*'%$_;\\(\\)]*)?$"
		   /* 
		    * Per the instructor: 
		    * Programming based testing would have a list of URLs stored somewhere 
		    * as a unit test asset, and the unit test would read the set of URLs in
		    *  and iterate through the list until it hits an assert that fails. For
		    *   a random test, the unit test would execute the randomizer and then 
		    *   start feeding the URLs to the isValid method.
		    */
		   
		   
		   assertTrue(urlvalidator.isValid(null));
		   
	   }
	   


	}
