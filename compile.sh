BUILT=build/

if [ ! -d "$BUILT" ]; then
    echo "Ejecutar primero install.sh"
else 
    cd build/
    cmake ..
    make
    mv client ..
    mv server ..
fi
