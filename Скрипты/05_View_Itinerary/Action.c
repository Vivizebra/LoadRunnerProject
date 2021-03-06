Action()
{

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_start_transaction("05_View_Itinerary");

	lr_start_transaction("WebTours");
	web_reg_save_param ("corUserSession","LB= name=\"userSession\" value=\"","RB=\"/>", LAST);
    web_reg_find("Text=enter your account","SaveCount=StartCount","Fail=NotFound",LAST);


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

	lr_think_time(16);

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
		"Name=login.x", "Value=66", ENDITEM, 
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

        if(atoi(lr_eval_string("{ItineraryCount}"))>2)

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

	lr_think_time(6);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t4.inf", 
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


	lr_end_transaction("05_View_Itinerary",LR_AUTO);

	return 0;
}