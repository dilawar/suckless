function initDB
{
    dbPath=$1
    if [ ! -f $dbPath ]; then
        echo "First time run.. Creating database..."
    fi
    # name is id and version together.
    # installed 0 means fully installed, > 0 means how many files are missing.
    # < 0 means not working, broken.

    TABLE1=`sqlite3 $DBPATH "CREATE TABLE IF NOT EXISTS package \
        (name VARCHAR NOT NULL \
        , id VARCHAR \
        , version VARCHAR \
        , installedOn DATETIME \
        , type VARCHAR \
        , path VARCHAR \
        , installed INTEGER \
        , PRIMARY KEY (name, version) \
        )"`
    TABLE2=`sqlite3 $DBPATH "CREATE TABLE IF NOT EXISTS files \
        (name VARCHAR \
        , id VARCHAR \
        , belongsTo VARCHAR \
        , version VARCHAR \
        , comment TEXT \
        , description TEXT \
        , type VARCHAR \
        , url VARCHAR \
        , isExists CHARACTER \
        , PRIMARY KEY (name, version) \
        , FOREIGN KEY (belongsTo) REFERENCES package(name) \
        )"`

    TABLE3=`sqlite3 $DBPATH "CREATE TABLE IF NOT EXISTS dependency \
        (name VARCHAR NOT NULL \
        , neededFor VARCHAR \
        , requiredBy VARCHAR  \
        , FOREIGN KEY (name) REFERENCES files (name) \
        , FOREIGN KEY (neededFor) REFERENCES package (name) \
        , FOREIGN KEY (requiredBy) REFERENCES package (name) \
        )"`
}


function insertintoDB
{
    pkg=`echo $(basename $1) | sed -e "s/.files//"`
    pkgName=${pkg%%-*}
    pkgVersion=${pkg##*-}
    dbName=$2
    colorPrint "INFO" "Processing package $pkgName, $pkgVersion"
    sqlite3 $dbName "INSERT OR REPLACE INTO package \
        (name, id, version, installed) VALUES \
        ('$pkg', '$pkgName', '$pkgVersion', '0') \
        "
    filetype="unknown"
    allInstalled="True"
    query=""
    while read line
    do
        # check if $line is a valid filename
        newLine=${line##/*/}
        if [[ $newLine ]]; then
            if [[ -f $line ]]; then
                if [[ -x $line ]]; then
                    filetype="executable"
                elif [[ $line == *"/lib/"* ]]; then
                    filetype="libary"
                elif [[ $line == *"/include/"* ]]; then
                    filetype="include"
                elif [[ $line == *"/man/"* ]]; then
                    filetype="manual"
                elif [[ $line == *"/doc/"* ]]; then
                    filetype="doc"
                elif [[ $line == *"texmf"* ]]; then
                    filetype="tex"
                elif [[ $line == *"locale"* ]]; then
                    filetype="locale"
                else
                    filetype="unknown"
                fi
                # prepare a query to insert 
                query="$query INSERT OR REPLACE INTO files \
                    (name, belongsTo, type, isExists) VALUES \
                    ('$line', '$pkg', '$filetype', 'true');" 
            else
                # Add a missing file line in missing table
                colorPrint "WARN" "Broken package?" "$line missing."
                query="$query INSERT OR REPLACE INTO files \
                    (name, belongsTo, type, isExists) VALUES \
                    ('$line', '$pkg', '$filetype', 'false');" 
                query="$query UPDATE package SET  \
                    installed=installed+1 where name='$pkg';" 
            fi
        fi
    done < $1
    echo $query | sqlite3 $dbName 
}
