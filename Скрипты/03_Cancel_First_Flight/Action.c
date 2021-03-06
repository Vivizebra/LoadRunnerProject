Action()
{

	lr_start_transaction("03_Cancel_First_Flight");

	lr_start_transaction("WebTours");
	
	web_reg_find("Text=enter your account","SaveCount=StartCount","Fail=NotFound",LAST);
	web_reg_save_param ("corUserSession","LB= name=\"userSession\" value=\"","RB=\"/>", LAST);

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

	lr_think_time(40);

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
		"Name=login.x", "Value=45", ENDITEM, 
		"Name=login.y", "Value=13", ENDITEM, 
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
	web_reg_find("Text=No flights have been reserved","SaveCount=NoFlights",LAST);
	
	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(27);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

		if(atoi(lr_eval_string("{ItineraryCount}"))>2)

        {
        lr_end_transaction("Select_Itinerary",LR_PASS);
        }
		else
        {
        lr_end_transaction("Select_Itinerary",LR_FAIL);
        }


	
	if(atoi(lr_eval_string("{NoFlights}"))<1)
	{
	lr_start_transaction("Get_ID");
	web_reg_save_param ("compIDToDelete","LB= name=\"flightID\" value=\"","RB=-", LAST);
	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(27);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("Get_ID",LR_AUTO);
	
	lr_start_transaction("Cancel_First");
	web_reg_find("Text=No flights have been reserved","SaveCount=NoFlightsAfterDeletion",LAST);
	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(141);

	web_submit_form("itinerary.pl", 
		"Snapshot=t5.inf", 
		ITEMDATA, 
		"Name=1", "Value=on", ENDITEM, 
		"Name=removeFlights.x", "Value=20", ENDITEM, 
		"Name=removeFlights.y", "Value=4", ENDITEM, 
		LAST);
	lr_end_transaction("Cancel_First",LR_AUTO);
	}
	else
	{
	lr_start_transaction("Cancel_First");
	lr_end_transaction("Cancel_First",LR_PASS);
	}
	
	lr_start_transaction("Confirm_Deletion");
	if(atoi(lr_eval_string("{NoFlightsAfterDeletion}"))<1)
		{
		
	lr_start_transaction("Get_ID_To_Compare");
    web_reg_save_param ("compIDAfterDelete","LB= name=\"flightID\" value=\"","RB=-", LAST);
   /* web_reg_find("Text={compIDToDelete}","SaveCount=IDCheck","Fail=Found",LAST);*/
	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(27);

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);
	lr_end_transaction("Get_ID_To_Compare",LR_AUTO);
	if(atoi(lr_eval_string("{compIDToDelete}"))!=atoi(lr_eval_string("{compIDAfterDelete}")))
	{
	lr_end_transaction("Confirm_Deletion",LR_PASS);	
	}
	else
	{
	lr_end_transaction("Confirm_Deletion",LR_FAIL);
	}
        }
		else
        {
        lr_end_transaction("Confirm_Deletion",LR_PASS);
        }
	
	lr_start_transaction("Sign_Off");

	web_reg_find("Text=enter your account","SaveCount=AccountCount","Fail=NotFound",LAST);
	
	web_revert_auto_header("Sec-Fetch-User");

	lr_think_time(19);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t7.inf", 
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


	lr_end_transaction("03_Cancel_First_Flight",LR_AUTO);

	return 0;
}