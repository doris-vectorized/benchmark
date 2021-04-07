header_dir=$(ls ../src/vec)

for header in $header_dir
do
	sed -i "s/#include <$header/#include <vec\/$header/g" $1
done
