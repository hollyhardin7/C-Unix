mkdir $1

mkdir $1/Dir1
chmod 770 $1/Dir1
touch $1/Dir1/File1
chmod 400 $1/Dir1/File1

mkdir $1/Dir2
chmod 775 $1/Dir2
touch $1/Dir2/File2
chmod 640 $1/Dir2/File2

mkdir $1/Dir1/Dir3

mkdir $1/Dir1/Dir3/Dir4
chmod 750 $1/Dir1/Dir3/Dir4
touch $1/Dir1/Dir3/Dir4/File3
chmod 200 $1/Dir1/Dir3/Dir4/File3
touch $1/Dir1/Dir3/Dir4/File4
chmod 666 $1/Dir1/Dir3/Dir4/File4

chmod 000 $1/Dir1/Dir3
