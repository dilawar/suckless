#!/bin/bash   
set +e
cd ./dmenu/     && sudo make clean install && cd ..
cd ./dwm/ && sudo make clean install && cd ..
cd ./dwmstatus && sudo make clean install && cd ..
cd ./lock && make && sudo make install && cd ..
echo "exec dwm" > $HOME/.xinitc
echo "dwmstatus" | sudo tee -a /etc/rc.local
