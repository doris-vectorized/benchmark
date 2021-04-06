header=$(echo "$1" | cut -d "/" -f 1,2,3,4)
name=$(echo "$1" | cut -d "/" -f 5 | sed 's/^[A-Z]/\l&/g' | sed "s/[ABCDEFGHIJKLMNOPQRSTUVWXYZ]/_\l&/g")

echo $1
echo $header/$name.bak

cp $1 $header/$name.bak

sed -i "s/namespace DB/namespace doris::vectorized/g" $header/$name.bak
python3 change_include.py $header/$name.bak


