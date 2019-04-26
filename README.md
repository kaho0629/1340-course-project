# 1340-course-project

## Problem Statement
Tracking of their income and expense is a good way to manage their wealth more effectively. If people do not cultivate a good habit to manage their money, it would affect the plan of the future months or even years! With the popularity of electronics, using digital tools is a good way to help us to manage our money. Therefore, we are going to build up a simple and multifunction accounting system to track user financial status. By using different components, we can build up the basis of our programme. The followings are the basic functions of the programme:
1.	Income and expenses records:
-	User can add records of their income and expense
2.	Information of records:
-	User can detail the records by adding dates, types of income and expense or accounts
3.	View of records
-	User can view their records by categories in details
4.	Statement of records
-	User can view the daily, monthly or yearly statement.
5.	Budget setting.
-	User can set the limits on their budget daily, monthly and yearly.
6.	Edit and recover the records
-	User can edit and recover their previous records.
7.	Suggestion in wealth allocation
-	We can give a simple saving plan or expanse plan to our user by using their record.
Those functions are the basic idea of our programme. We may add some new functions if there is a spark of new idea.


## Problem setting
1.	What are the basis components of our programme?
-	Record libraries, compilers, back up files
2.	How is your programme function?
-	User can first input the keywords trigger the function. For example, user input “Add E 100” and it will be translated as add $100 expense record into libraries.
3.	How to add information to each record?
-	We can provide some basic options to user in each information(e.g. date: now or customize, types of income, expanse: work, food, travel, or add a new type…)
4.	How users view their previous record?
-	First, type keyword “Record”. Then we can provide different options to sort and hide different types of records
-	The following is an ideal example
-	“Record I monthly parttime” This command will provide the “record” of “parttime” “I”ncome and shown in “monthly”. 
5.	How users view their previous statement?
-	First, type keyword “Statement”. Then we can provide options in different time scale and they can view the expense or income report within that time.
-	“Statement monthly 3/2019” This command will provide the “statement” in “3/2019”
6.	How users set their budget?
-	First, type keyword “Budget”. Then we can provide options in different time scale and types of expense. Also, they can set the limits to give alerts when they used over a certain amount.
-	“Budget coming weekly eat 1500” This command will set alert in 7 days afterwards. When the expense in eating is over $1500. “Over Budget!!” is pop-up.
-	“Budget present monthly eat 5000” This command will set alert in present month. When the expense in eating is over $5000 in the same month. “Over Budget!!” is pop-up.
7.	How users edit their records/ budget?
-	No matter how users add a complete modification to the system(e.g. added an expense with full details), the records and budget files will backup once(up to last 5 modification). User can recover up to last 5 modification.
-	Also, users can modify their records directly.
-	“Edit budget coming weekly eat 1500 correct present weekly eat 1500” This command will correct the budget setting from coming week to present week.
-	“Edit budget coming weekly eat 1500 delete” This command will delete the budget setting.

- Users are able to compare the income or expense on a certain aspect between different time period. For example, users can type "Compare E food", the system will output the amount of money spent on food last month and this month. User can have a clear understanding on the change of their spending habit. 

We expect most of the problems should appear when designing and coding. However, it gives a basic blueprint to our programme.
