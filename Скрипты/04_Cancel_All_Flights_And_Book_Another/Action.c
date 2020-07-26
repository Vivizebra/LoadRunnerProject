Action()
{

	lr_start_transaction("04_Cancel_All_And_Book_Another");

	lr_start_transaction("WebTours");
	
	    web_reg_save_param ("corUserSession","LB= name=\"userSession\" value=\"","RB=\"/>", LAST);
    web_reg_find("Text=enter your account","SaveCount=StartCount","Fail=NotFound",LAST);


	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

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
	
	    web_reg_find("Text=you can search","SaveCount=WelcomeCount","Fail=NotFound",LAST);

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(15);

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
		"Name=login.x", "Value=72", ENDITEM, 
		"Name=login.y", "Value=8", ENDITEM, 
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


	lr_start_transaction("Select_Itinerary");
	
	    web_reg_find("Text=Itinerary","SaveCount=ItineraryCount","Fail=NotFound",LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(17);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

        if(atoi(lr_eval_string("{ItineraryCount}"))>0)

        {
        lr_end_transaction("Select_Itinerary",LR_PASS);
        }

    else
        {
        lr_end_transaction("Select_Itinerary",LR_FAIL);
        }

	lr_start_transaction("Cancel_All");
	
	web_reg_find("Text=No flights","SaveCount=CancelCount","Fail=NotFound",LAST);

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(9);

	web_submit_data("itinerary.pl", 
		"Action=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=flightID", "Value=0-7-JB", ENDITEM, 
		"Name=removeAllFlights.x", "Value=38", ENDITEM, 
		"Name=removeAllFlights.y", "Value=12", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		LAST);

    if(atoi(lr_eval_string("{CancelCount}"))>0)

        {
        lr_end_transaction("Cancel_All",LR_PASS);
        }

    else
        {
        lr_end_transaction("Cancel_All",LR_FAIL);
        }


	lr_start_transaction("Select_Flights");
	
	    web_reg_find("Text=Departure City","SaveCount=CityCount","Fail=NotFound",LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(31);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t5.inf", 
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
	
	    web_reg_find("Text=departing from","SaveCount=DepartureCount","Fail=NotFound",LAST);

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(49);

	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={departPar}", ENDITEM, 
		"Name=departDate", "Value=07/27/2020", ENDITEM, 
		"Name=arrive", "Value={arrivePar}", ENDITEM, 
		"Name=returnDate", "Value=07/28/2020", ENDITEM, 
		"Name=numPassengers", "Value={passengersPar}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefPar}", ENDITEM, 
		"Name=seatType", "Value={seatTypePar}", ENDITEM, 
		"Name=findFlights.x", "Value=63", ENDITEM, 
		"Name=findFlights.y", "Value=6", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

        if(atoi(lr_eval_string("{DepartureCount}"))>0)

        {
        lr_end_transaction("Flight_Search",LR_PASS);
        }

    else
        {
        lr_end_transaction("Flight_Search",LR_FAIL);
        }


	lr_think_time(16);

	lr_start_transaction("Flight_Selection");
	
	web_reg_find("Text=Street Address","SaveCount=StreetCount","Fail=NotFound",LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value=362;107;07/27/2020", ENDITEM, 
		"Name=numPassengers", "Value={passengersPar}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={seatTypePar}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefPar}", ENDITEM, 
		"Name=reserveFlights.x", "Value=51", ENDITEM, 
		"Name=reserveFlights.y", "Value=14", ENDITEM, 
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
	
	    web_reg_find("Text=Thank you for booking","SaveCount=BookingCount","Fail=NotFound",LAST);

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(42);

	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value=Jojo", ENDITEM, 
		"Name=lastName", "Value=Bean", ENDITEM, 
		"Name=address1", "Value={streetPar}", ENDITEM, 
		"Name=address2", "Value={cityPar}", ENDITEM, 
		"Name=pass1", "Value=Jojo Bean", ENDITEM, 
		"Name=pass2", "Value=", ENDITEM, 
		"Name=creditCard", "Value={creditPar}", ENDITEM, 
		"Name=expDate", "Value={expPar}", ENDITEM, 
		"Name=oldCCOption", "Value=", ENDITEM, 
		"Name=numPassengers", "Value={passengersPar}", ENDITEM, 
		"Name=seatType", "Value={seatTypePar}", ENDITEM, 
		"Name=seatPref", "Value={seatPrefPar}", ENDITEM, 
		"Name=outboundFlight", "Value=362;107;07/27/2020", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=55", ENDITEM, 
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
	web_reg_find("Text=Itinerary","SaveCount=ItineraryCount","Fail=NotFound",LAST);

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(27);

	web_url("Itinerary Button_2", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

        if(atoi(lr_eval_string("{ItineraryCount}"))>0)

        {
        lr_end_transaction("Select_Itinerary",LR_PASS);
        }

    else
        {
        lr_end_transaction("Select_Itinerary",LR_FAIL);
        }

	lr_start_transaction("Sign_Off");
	
	web_reg_find("Text=enter your account","SaveCount=AccountCount","Fail=NotFound",LAST);

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(24);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t10.inf", 
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


	lr_end_transaction("04_Cancel_All_And_Book_Another",LR_AUTO);

	return 0;
}