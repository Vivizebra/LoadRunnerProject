Action()
{

	web_set_sockets_option("SSL_VERSION", "2&3");
	
	web_set_max_html_param_len("9999"); 

	lr_start_transaction("01_Book_Flight_And_Visit_Itirary");

	lr_start_transaction("WebTours");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_save_param ("corUserSession","LB= name=\"userSession\" value=\"","RB=\"/>", LAST);
	web_reg_find("Text=enter your account","SaveCount=StartCount","Fail=NotFound",LAST);
	
	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	if(atoi(lr_eval_string("{StartCount}"))>0)

		{
		lr_end_transaction("WebTours",LR_PASS);
		}

	else
		{
		lr_end_transaction("WebTours",LR_FAIL);
		}

	lr_start_transaction("Login");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(21);
	
	web_reg_find("Text=you can search","SaveCount=WelcomeCount","Fail=NotFound",LAST);
	
	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={corUserSession}", ENDITEM,
		"Name=username", "Value={loginPar}", ENDITEM,
		"Name=password", "Value={passPar}", ENDITEM,
		"Name=login.x", "Value=50", ENDITEM,
		"Name=login.y", "Value=3", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

		if(atoi(lr_eval_string("{WelcomeCount}"))>0)

		{
		lr_end_transaction("Login",LR_PASS);
		}

	else
		{
		lr_end_transaction("Login",LR_FAIL);
		}

	lr_start_transaction("Select_Flights");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(40);
	
	web_reg_find("Text=Departure City","SaveCount=CityCount","Fail=NotFound",LAST);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

		if(atoi(lr_eval_string("{CityCount}"))>0)

		{
		lr_end_transaction("Select_Flights",LR_PASS);
		}

	else
		{
		lr_end_transaction("Select_Flights",LR_FAIL);
		}

	lr_start_transaction("Flight_Search");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(34);
	
	web_reg_save_param ("corOutboundFlight","LB= name=\"outboundFlight\" value=\"","RB=\"", LAST);
	
	web_reg_find("Text=departing from","SaveCount=DepartureCount","Fail=NotFound",LAST);
	web_reg_find("Text=<B>{departPar}</B> to <B>{arrivePar}</B>","SaveCount=CityCheck","Fail=NotFound",LAST);
	
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={departPar}", ENDITEM, 
		"Name=departDate", "Value={currentDatePar}", ENDITEM, 
		"Name=arrive", "Value={arrivePar}", ENDITEM, 
		"Name=returnDate", "Value={returnDateParam}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seatPrefPar}", ENDITEM, 
		"Name=seatType", "Value={seatTypePar}", ENDITEM, 
		"Name=findFlights.x", "Value=30", ENDITEM, 
		"Name=findFlights.y", "Value=10", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

		if(atoi(lr_eval_string("{DepartureCount}"))>0 && atoi(lr_eval_string("{CityCheck}"))>0)

		{
		lr_end_transaction("Flight_Search",LR_PASS);
		}

	else
		{
		lr_end_transaction("Flight_Search",LR_FAIL);
		}

	lr_think_time(45);
	
	lr_start_transaction("Flight_Selection");

	/*lr_output_message("Value is %s",lr_eval_string("{corOutboundFlight}"));
	lr_output_message("Value is %s",lr_eval_string("{loginPar}"));*/

	web_reg_find("Text=Street Address","SaveCount=StreetCount","Fail=NotFound",LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={corOutboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatTypePar}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefPar}", ENDITEM, 
		"Name=reserveFlights.x", "Value=49", ENDITEM, 
		"Name=reserveFlights.y", "Value=5", ENDITEM, 
		LAST);

		if(atoi(lr_eval_string("{StreetCount}"))>0)

		{
		lr_end_transaction("Flight_Selection",LR_PASS);
		}

	else
		{
		lr_end_transaction("Flight_Selection",LR_FAIL);
		}



	lr_start_transaction("Payment_Data");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(46);
	
	web_reg_find("Text=Thank you for booking","SaveCount=BookingCount","Fail=NotFound",LAST);

	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={loginPar}", ENDITEM, 
		"Name=lastName", "Value=Bean", ENDITEM, 
		"Name=address1", "Value={streetPar}", ENDITEM, 
		"Name=address2", "Value={cityPar}", ENDITEM, 
		"Name=pass1", "Value=Jojo Bean", ENDITEM, 
		"Name=creditCard", "Value={creditPar}", ENDITEM, 
		"Name=expDate", "Value={expPar}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatType", "Value={seatTypePar}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefPar}", ENDITEM, 
		"Name=outboundFlight", "Value={corOutboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=40", ENDITEM, 
		"Name=buyFlights.y", "Value=7", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);

		if(atoi(lr_eval_string("{BookingCount}"))>0)

		{
		lr_end_transaction("Payment_Data",LR_PASS);
		}

	else
		{
		lr_end_transaction("Payment_Data",LR_FAIL);
		}


	lr_start_transaction("Select_Itinerary");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(30);
	
	web_reg_find("Text=Itinerary","SaveCount=ItineraryCount","Fail=NotFound",LAST);
	web_reg_find("Text={departPar}  for {arrivePar}","SaveCount=CityCheck2","Fail=NotFound",LAST);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(126);

	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);
	
		if(atoi(lr_eval_string("{ItineraryCount}"))>2 && atoi(lr_eval_string("{CityCheck2}"))>0)

		{
		lr_end_transaction("Select_Itinerary",LR_PASS);
		}

	else
		{
		lr_end_transaction("Select_Itinerary",LR_FAIL);
		}


	lr_start_transaction("Sign_Off");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(33);
	
	web_reg_find("Text=enter your account","SaveCount=AccountCount","Fail=NotFound",LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);
	
		if(atoi(lr_eval_string("{AccountCount}"))>0)

		{
		lr_end_transaction("Sign_Off",LR_PASS);
		}

	else
		{
		lr_end_transaction("Sign_Off",LR_FAIL);
		}


	lr_end_transaction("01_Book_Flight_And_Visit_Itirary",LR_AUTO);

	return 0;
}