#!/bin/bash
# The line above specifies where the bash interpreter is located.

# We set this variable to a value that changes only if the user chooses to exit.
# So, this variable is used in the while loop that generates the menu each time.
temp_check=777

# We set these file path variables to blank, in order to be initialized for the following controls.
path_of_file=""
path_to_save=""

# Printing the program title on the screen.
echo $'\nOPERATING SYSTEMS EXERCISE #1 \n'

#The while loop that runs in order to generate the menu.
#It runs until the user chooses to exit.
while [ $temp_check -eq 777 ]; do

	# This part of the code prints the menu.
	echo $'-------------------------------\n'
	echo $'\tMAIN MENU\n'
	echo "[1] Load a file with grades"
	echo "[2] Show a student's grades"
	echo "[3] Change a student's grades"
	echo "[4] Show the grade list"
	echo "[5] Save the grade list"
	echo $'[6] Exit\n'
	echo $'-------------------------------\n'
	echo -n "Please select an option: "

	# Here the program waits for the user to enter his/her choice.
	# The choice is stored in a variable that is used below in the if block.
	# The choice is expressed as a number from 1-6.
	read choice
	
	# The whole if block is used to separate the various operations of the program.
	# Each part is executed according to the user's choice.
	
	# This part is executed when the user chooses option 1. 
	# This means that the user wants to load a grade list.
	if [ $choice -eq 1 ]; then

		# The message that is printed for option 1.
		# It asks the user to enter a file path.
		echo $'\n-------------------------------\n'	
		echo "You have chosen to load a file with grades."
		echo "Please enter the path of the file:"
		
		# Infinite while loop used to control whether the file path that was entered is valid or not.
		while :
		do
			# The program waits for the user to enter a file path.
			read path_of_file
			
			# This if block is used to control the various possible cases.
			# The first one is executed when the user hasn't entered a file path at all.
			# The second one is executed when the user has entered a file path that doesn't exist.
			# The third one is executed when the user has entered a valid file path.
			if [ -z $path_of_file ]; then
				# The message that is printed to inform the user of his choice.
				echo "You have not entered a file path."
				# As proposed in the exercise, grades.txt is set as the file path, if the user hasn't entered one.
				path_of_file="grades.txt"
				# Now that the file path is set, the control loop ends.
				break
			elif [ ! -e $path_of_file ]; then
				# The message that printed to inform the user and ask for a valid file path.
				echo $'The path you have entered is invalid.\nPlease enter a valid one:'
			elif [ -e $path_of_file ]; then
				# This message simply prints nothing.
				# It is used for aesthetic reasons, to print a new line that echo prints anyway.
				echo $''
				# Now that the file path is set, the control loop ends.
				break
			fi
		done
		
		# Message informing the user what file was loaded as a grade list in the end.
		echo $'The file '$path_of_file$' was loaded.\n'
		# Here the data of the chosen list are copied to a temporary file.
		# The temporary file temp.txt is created and will be used for the performance of the changes.
		cat $path_of_file > temp.txt

	# This part is executed when the user chooses option 2. 
	# This means that the user wants to view a student's grades.	
	elif [ $choice -eq 2 ]; then
		
		# This if block is a control. It checks whether a grade list is loaded.
		# If not, it loads by default the grades.txt.
		# This could happen if the user chose this option before the load of a grade list.
		if [ -z $path_of_file ]; then
			path_of_file="grades.txt"
		fi

		# The message that is printed for option 2.
		# It asks the user to enter the student's number (or AM).
		echo $'\n-------------------------------\n'
		echo "You have chosen to view a student's grades."
		echo "Please enter his student number (AM):"
		
		# Infinite while loop to check whether the student number exists or not.
		while :
		do
			# The program waits for the user to enter a student's number.
			read student_number
			
			# This if block is used to check if the user wants to return to the main menu.
			# This could happen when the user didn't remember a valid student number.
			# If so, the user can enter the word MENU and exit option 2.
			if [ $student_number = "MENU" ]; then
				# Exit the while loop and return to the main menu.
				break
			fi
			
			# This if block is used to check which file will be considered as a source list.
			# If the user hasn't chosen option 1 yet or, there will be no temp.txt.
			# So, the grades.txt is loaded by default and option 2 can be executed normally.
			# If the user has chosen option 1, then the temp.txt is selected.
			# This is done because temp.txt includes any possible change performed on the list.
			# And the user may not have chosen to save the changed grade list yet.
			if [ -e temp.txt ]; then
				# Sets temp.txt as grade list.
				temp_path_of_file="temp.txt"
			else
				# Sets the default grade list.
				temp_path_of_file=$path_of_file
			fi
			
			# A control to see whether the student exists in the list.
			# If the student exists, the return of the grep command will be greater than 0.
			# If the student doesn't exist, the return will be 0.
			# This is done this way because usually the AM are big numbers. 
			# If we had AM varying from 0-10, as the grades do, then the check would be done with the awk command.
			exists="$(grep -c $student_number $temp_path_of_file)"
			
			# If block to check (in addition to the above command) if a student exists.
			if [ $exists -gt 0 ]; then
				# This code will be executed if the student exists.
				# The grep command returns the whole line where the AM is.
				# The awk command prints the information for the student.
				grep -i $student_number $temp_path_of_file | awk 'BEGIN { FS=","} { printf "\n%s took %s.\n\n", $2, $3 } '
				break
			else
				# This message is printed when the student doesn't exist.
				# It asks the user to enter a valid AM.
				# It also gives the user the option to exit this function, by entering the word MENU.
				echo -n $'\nThe AM you entered does not exist.'
				echo $' You can return to the main menu by entering the word "MENU", or you can enter a valid AM:'
			fi
		done

	# This part is executed when the user chooses the option 3. 
	# This means that the user wants to change a student's grades.
	elif [ $choice -eq 3 ]; then

		# This if block is a control. It checks whether a grade list is loaded.
		# If not, it loads by default the grades.txt.
		# This could happen if the user chose this option before the load of a grade list.
		if [ -z $path_of_file ]; then
			path_of_file="grades.txt"
		fi
		
		# This if block checks whether the temporary temp.txt exists
		# If it doesn't, it creates it and copies the data from the current grade list to it.
		# temp.txt is necessary to perform any changes on the list, without changing the loaded list.
		# By this any unwanted changes could be avoided. 
		# Only if the user chose to save the list, would the changes be done to the loaded grade list.
		if [ ! -e temp.txt ]; then
			cat $path_of_file > temp.txt
		fi

		# This message is printed for option 3.
		# It asks the user to enter the student's number and the new grade.
		echo $'\n-------------------------------\n'	
		echo -n "You have chosen to change a student's grades."
		echo " Please enter his/her AM and the new grade:"
		
		# Infinite while loop to check whether the AM and the new grade are valid.
		while :
		do
			
			# The program waits for the user to enter a student's number and a new grade.
			read student_number
			read new_grade

			# A control to see whether the student exists in the list.
			# If the student exists, the return of the grep command will be greater than 0.
			# If the student doesn't exist, the return will be 0.
			# This is done this way because usually the AM are big numbers. 
			# If we had AM varying from 0-10, as the grades do, then the check would be done with the awk command.
			exists="$(grep -c $student_number $path_of_file)"

			# While loop to check the validity of the student number.
			while [ $exists -eq 0 ]; do
				
				# This message warns the user that the entered AM isn't valid.
				# It asks the user to enter a new one.
				echo -n $'The AM you entered does not exist. Please enter a valid AM:'
				
				# The program waits for the user to enter a student number.
				read student_number
				
				# Same control as above, performed again in the loop.
				# This is because we need to recontrol the existance of the student number.
				exists="$(grep -c $student_number $path_of_file)"
				
				# If block to check the result of the grep command.
				# If the student exists, then the break is executed.
				# If not, the user remains in the loop until the AM is valid.
				if [ $exists -gt 0 ]; then
					break
				fi
			done
		
			# While loop to check the validity of the new grade.
			# If the entered grade is lower than zero or greater than 10, the loop is executed.
			while [  $new_grade -lt 0 ] || [ $new_grade -gt 10 ]; do
				
				# This messages warns the user that the entered grade isn't valid.
				# It asks the user to enter a new one.
				echo "The grade you entered is invalid. Please enter a valid one: "
				
				# The program waits for the user to enter a new grade.
				read new_grade
			
				# If block to check whether the new grade is valid or not.
				# If it is, then the break is executed and the user exits the loop.
				# If not, the user remains in the loop until a valid grade is given.
				if [ $new_grade -ge 0 ] && [ $new_grade -le 10 ]; then
					break
				fi
			done
			
			# We save the old grade in the old_grade variable before any change is performed.
			# This is because we need to print it out in the end of this function.
			# The grep command returns the whole line where the student number is found.
			# The awk command returns the third part of the above line (separated with commas).
			# The result is saved in the old_grade variable.
			old_grade="$(grep -i $student_number temp.txt | awk 'BEGIN { FS=","} { print $3 } ')"
			
			# We save the new grade by saving the whole new line in the new_line variable.
			# This is because of the way the change is done. It will be explained below.
			# For now, the grep command returns the whole old line with the student's info.
			# Then, awk prints out the new line in the same format, this time changing the grade field.
			# The value of new_grade variable that was given from the user replaces the old grade.
			new_line="$(grep -i $student_number temp.txt | awk -v n_g=$new_grade 'BEGIN { OFS=FS="," } { print $1,$2,n_g }')"
			
			# The sed command deletes the whole line where the given student number is given.
			# The line is not actually deleted, it's rather not printed out.
			# So, the result of sed is redirected and saved in a new temporary file, temp_i.txt.
			sed "/$student_number/d" temp.txt > temp_i.txt
			
			# The echo command prints out the new line with the new student data. 
			# The result of echo is redirected and added in the end of the text that's in temp_i.txt
			echo $new_line >> temp_i.txt
			
			# Now, temp_i.txt includes all the data of the grade list.
			# The only thing that needs to be done is sorting.
			# So, sort sorts the data of temp_i.txt. 
			# Since AM is the first character series in each line, the sorting is done correctly.
			# The result of sort is then redirected and saved in temp.txt.
			sort temp_i.txt > temp.txt
			
			# We delete temp_i.txt now, since the change is done.
			# The deletion of temp_i.txt is necessary, if we want to perform another change.
			# Also, because we don't want to leave any extra files after the execution of the program.
			rm temp_i.txt
			
			# This is when we print out the data of the student, including the old grade.
			# We use grep again to return the whole line where the AM is found.
			# Then awk to print out the data in the desired order.
			grep -i $student_number temp.txt | awk -v o_g=$old_grade 'BEGIN { OFS=FS="," } { print $2" has now "$3" instead of "o_g"." }' 
			
			# Finally, after the change was done, we exit the loop.
			break
		done 
	
	# This part is executed when the user chooses the option 4. 
	# This means that the user wants to view the grade list.
	elif [ $choice -eq 4 ]; then

		# This message is printed for option 4.
		echo $'\n-------------------------------\n'	
		echo $'You have chosen to view the grade list.\n'
		
		# If block to check from which file will the list be printed.
		if [ -e temp.txt ]; then
			# If there are any changes, there will be a temp.txt. 
			# So, the data printed out will come from that file.
			# awk prints each line of the list, and before this prints a simple title.
			awk -F"," 'BEGIN {print "Grade\t AM\t\tName\t";} { print $3,"\t",$1,"\t",$2; }' temp.txt | more
		elif [ ! -z $path_of_file ]; then
			# If a valid file was loaded, without any changes being done, then it's used.
			# awk prints each line of the list, and before this prints a simple title.
			awk -F"," 'BEGIN {print "Grade\t AM\t\tName\t";} { print $3,"\t",$1,"\t",$2; }' $path_of_file | more
		else
			# If neither a valid grade list nor a temporary file is found, then this message is printed.
			# It informs the user that no grade list was loaded.
			echo $'Unfortunately, no grade list is loaded.\n'
		fi	
		
	# This part is executed when the user chooses the option 5. 
	# This means that the user wants to save the grade list.	
	elif [ $choice -eq 5 ]; then

		# This message is printed for option 5.
		echo $'\n-------------------------------\n'
		echo -n "You have chosen to save the grade list."
		
		# If block that is used for the two different occasions. 
		# If there have been changes, it saves the temp.txt to the specified file.
		# If not, it prints out a message informing the user.
		if [ -e temp.txt ]; then
		
			# It asks the user to enter the path where the list should be saved.
			echo " Please enter the path of the file to which you want to save it:"
			
			# The program waits for the user to enter a file path.
			read path_to_save
		
			# If the user hasn't given any path, grades.txt is chosen by default.
			if [ -z $path_to_save ]; then
				path_to_save="grades.txt"
			fi
		
			# If temp.txt exists, it means that there have been changes.
			# So, the data of temp.txt are saved to the specified file path.
			if [ -e temp.txt ]; then
				cat temp.txt > $path_to_save
			fi
			
			# This message informs the user where the list was saved.
			echo $'\nThe list was saved to '$path_to_save$'.\n'
		else
			# This message informs the user that no changes were done.
			echo $' There have not been any changes. Nothing to be saved.\n'
		fi
	
	# This part is executed when the user chooses the option 6. 
	# This means that the user wants to exit the program.	
	elif [ $choice -eq 6 ]; then
		
		# The message that is printed when the user has chosen to exit.
		echo $'\n-------------------------------\n'
		echo $'You have chosen to exit.'
		echo $'We hope to see you again.\n'
		
		# Here we check if a temporary text file was created in order to make the changes to the list possible.
		# If so, then it is deleted to leave no extra files in the system after the execution of the program.
		if [ -e temp.txt ]; then
			rm temp.txt
		fi
		
		# The variable that is used to control the while loop is changed.
		# So the control will have a negative result and the while loop will break.
		# Literally, the user will have exited the program.
		temp_check=000
	
	# This part is executed when the user enters a number different than 1, 2, 3, 4, 5, 6.
	else
		# This warning message is printed on the screen and the program returns to the main menu.
		echo $'\nYour selection was invalid.\nYou are redirected to the main menu.\n'
	fi
done
