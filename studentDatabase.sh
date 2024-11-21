# Shree Ganesha


while [ 1 ] 
do
	echo 1.Create 2.Display 3.Insert 4.Search 5.Modify 6.Delete 7.Exit

	echo "Enter Choice : "
	read ch 

	case $ch in 
		1)
			echo "Enter File Name : "
			read fname
			if [ -e $fname ] 
			then
				echo "File Already Exists"
			else
				>$fname   #file created , if existing then overwritten
				echo "File Created Success!"
			fi
			;;
		2)
			echo "Enter File Name : "
		       	read fname 
	       		if [ -e $fname ]
	       		then
		 		echo "The Content of File is : "
				sort -n $fname
			else
				echo "File not exists"
			fi
			;;
		3)
			echo "Enter File Name : "                                                   
			read fname
                        if [ -e $fname ]
                        then
				echo -n "Enter rollNo :"
			       	read roll
				grep -w "$roll" $fname
				ans=$?
				if [ $ans -eq 0 ]
				then
					echo "Record Already Exists! "
				else
					echo -n "Enter Name : "
					read name
					echo "$roll $name" >> $fname
					echo "Record Insertion Success"
				fi		
                        else
                                echo "File not exists"                                              
			fi
				;; 	
		4)
			echo "Enter File name : "
			read fname
		       if [ -e $fname ]
		       then
				echo -n "Enter rollNo : "
				read roll
				grep -w "$roll" $fname 
				ans=$?
				if [ $ans -eq 0 ]
				then
					echo "Record Found!!!"
				else
					echo "Record Not Found "
				fi
		       else
				echo "File not Found!" 
		       fi
			;;
		5)
			echo "Enter file name : "
		       	read fname
	       		if [ -e $fname ]
		 		then
					echo -n "Enter the Existing RollNo you want to modify : "
				      read roll
			      grep -w "$roll" $fname 
				ans=$?
		  		if [ $ans -eq 0 ]
				then
					echo "Enter new RollNo and NewName :"
					read nroll nname
					grep -w "$nroll" $fname
					ans=$?
					if [ $ans -eq 0 ]
					then
					    	echo "Record already exists please try with another rollNo "
				       else
					       	grep -v "$roll" $fname >> temp
					      	echo "$nroll $nname" >> temp
					     	rm $fname
						cp temp $fname 
						rm temp 
						echo "Record Modified Success!"
					fi	       
				else
					echo "Roll No not exists in records!"	
				fi


			else
				echo "File not Found ! "
			fi			
			;;		
		6)
			echo "Enter file name : "
			read fname
			if [ -e $fname ]
			then
				echo -n "Enter the rollNo you want to delete : "
				read roll
				grep -w "$roll" $fname 
				ans=$?
				if [ $ans -eq 0 ]
				then
					grep -v "$roll" $fname >> temp
					rm $fname
					cp temp $fname
					rm temp
					echo "Record Deletion Success!"	
				else
				echo "RollNo only does not exists!" 
				fi
			else
				echo "File Does not exists!"
			fi
			;;
		7)
			echo "Exiting the code bbye!"
			exit
			;;
		*)
			echo "Enter Valid Choice"
			;;
	esac
done
