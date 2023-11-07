c=0
while test $c!=7
do
echo "1.Create 2.View 3.Insert 4.Delete 5.Modify 6.Search 7.Exit"
read c
case "$c" in
"1")
echo "Enter the file name"
read name
touch "$name"
echo "Address book created Successfully"
;;
"2")
cat "$name"
;;
"3")
echo "Enter record in format -> id <space> First Name <space> Last Name <space> Address
<space> Contact <space> Email-ID"
read rec
echo "$rec" >> "$name"
echo "Record inserted successfully"
;;
"4")
echo "Enter the id of record to be deleted"
read id
sed -i "/$id/d" "$name"
echo "record deleted successfully"
;;
"5")
echo "Enter old contact"
read add
echo "Enter new contact"
read new
sed -i "s/$add/$new/" "$name"
echo "Record modified successfully"
;;
"6")
echo "Enter the record to be search"
read rec
grep -i "$rec" "$name"
;;
"7")
echo "Exit Bye"
exit
;;
esac
done
exit
