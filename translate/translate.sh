pathToTranslate="./translate/"
pathToPosition="./positions/"
cd $pathToPosition
for file in `find -type f -name "*.pos"`
do
	echo $file
    cd ..
	python3 translate.py --input=$pathToPosition$file --output=$pathToTranslate$file
	cd $pathToPosition
done