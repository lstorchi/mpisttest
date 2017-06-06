MPI - C Examples# 

wget https://www.open-mpi.org/software/ompi/v2.1/downloads/openmpi-2.1.1.tar.gz 

mkdir workspace
cd workspace/
tar zxvf ../openmpi-2.1.1.tar.gz 

mkdir /home/$USER/local 

./configure --prefix=/home/$USER/local/ --enable-mpirun-prex-by-default --enable-static 

make -j4 

make install


git clone  https://github.com/lstorchi/mpisttest

