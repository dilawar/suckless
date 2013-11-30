function updateDB
{
    text=$(cat $1)
    pkg=`echo $(basename $1) | sed -e "s/.files//"`
    pkgName=$(echo $pkg | cut -d- -f1)
    pkgVersion=$(echo $pkg | cut -d- -f2)
    dbName=$2
    echo "+ Processing package $pkgName, $pkgVersion"
    filetype="unknown"
    allInstalled="True"
    for line in $text; do 
        if [ -f $line ]; then
            if [[ $line == *"bin"* ]]; then
                filetype="binary"
            elif [[ $line == *"lib"* ]]; then
                filetype="libary"
            elif [[ $line == *"include"* ]]; then
                filetype="include"
            elif [[ $line == *"man"* ]]; then
                filetype="manual"
            elif [[ $line == *"doc"* ]]; then
                filetype="doc"
            elif [[ $line == *"perl"* ]]; then
                filetype="perl"
            elif [[ $line == *"texmf"* ]]; then
                filetype="tex"
            elif [[ $line == *"locale"* ]]; then
                filetype="setting"
            else
                filetype="unknown"
            fi
            # prepare a query to insert 
        fi
    done
}
