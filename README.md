# Html Help Workshop Helper

A little helper program to create .hhp and .hhc snipets as well as .htm template files based on a text outline file

I found this to be a big time saver when drafting the help files for my Windows application

The input (outline) file looks something link this (note the tabs):

General topics;SBHgeneral.htm
	The purpose of your Secret Box;purpose.htm
		Importance of unique passwords for every site;importanceOfUnique.htm
	Getting help;gettingHelp.htm
	First time use;firstTimeUse.htm
		The secrets database;secretsDB.htm
		The master password;masterPW.htm
Search functionality;searchFunction.htm
	Simple searches;simpleSearch.htm
	Complex searches;complexSearch.htm


The tabs are used to specify the indentation on the toc file. The last level is assumed to be a document, otherwise, they are books. The semicolon separates the title of the topic from the htm file name. Note that this format is handy when creating "related topics" links in the HTML Help Workshop tool.

To use it, create the outline file in outline.txt and the baseline template file in template.txt, then run the program. Next, go into the HTNL Workshoop tool and create your project (be sure to create your baseline table of contents). Next, exit the tool and cut and paste the snipets into your .hhp and .hhc files. Finally, copy your template .htm files into your project folder. Re-open your project in the workshop and you should see all of your new .htm files and a valid table of contents based on your outline.

All you need to do now is fire up SeaMonkey on each of your template htm files to compose your actual help topics!

Note: If the string "xtitlex" is found anywhere in your baseline htm template file, it will be replaced with the title from the outline file in the generated template.
