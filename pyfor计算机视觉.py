sudo apt-get install libpng-dev libjpeg-dev libtiff-dev libxxf86vm1 libxxf86vm-dev libxi-dev libxrandr-dev
git clone --recursive https://github.com/openMVG/openMVG.git
mkdir openMVG_Build && cd openMVG_Build
sudo cmake -DCMAKE_BUILD_TYPE=RELEASE ../openMVG/src/
sudo cmake --build . --target install



hg clone https://bitbucket.org/eigen/eigen#3.2
mkdir eigen_build && cd eigen_build
cmake . ../eigen
make && sudo make install
sudo apt-get -y install libboost-iostreams-dev libboost-program-options-dev libboost-system-dev libboost-serialization-dev
sudo apt-get -y install libopencv-dev
sudo apt-get -y install libcgal-dev libcgal-qt5-dev
git clone https://github.com/cdcseacave/VCG.git vcglib
sudo apt-get -y install libatlas-base-dev libsuitesparse-dev
git clone https://github.com/ceres-solver/ceres-solver ceres-solver
mkdir ceres_build && cd ceres_build
cmake . ../ceres-solver/ -DMINIGLOG=ON -DBUILD_TESTING=OFF -DBUILD_EXAMPLES=OFF
make -j2 && sudo make install
cd ..
git clone https://github.com/cdcseacave/openMVS.git openMVS
mkdir openMVS_build && cd openMVS_build
cmake . ../openMVS -DCMAKE_BUILD_TYPE=Release -DVCG_ROOT="$~/openMVS/vcglib"
make -j2 && sudo make install

openMVG_main_SfMInit_ImageListing -i /home/li/test -o /home/li/test/out -k "2905;0;1416;0;2905.88; 1064;0;0;1"

openMVG_main_ComputeFeatures -i /home/li/test/out/sfm_data.json -o /home/li/test/out

openMVG_main_ComputeMatches -i /home/li/test/out/sfm_data.json  -o /home/li/test/out

openMVG_main_IncrementalSfM -i /home/li/test/out/sfm_data.json -o /home/li/test/out/out_Incremental_Reconstruction -m /home/li/test/out

openMVG_main_ExportUndistortedImages -i /home/li/test/out/sfm_data.json  -o /home/li/test/out/out_Incremental_Reconstruction/image

openMVG_main_ComputeSfM_DataColor -i /home/li/test/out/out_Incremental_Reconstruction/sfm_data.bin -o /home/li/test/out/out_Incremental_Reconstruction/colorized.ply

openMVG_main_openMVG2openMVS -i sfm_data.bin -o s.mvs

DensifyPointCloud s.mvs

ReconstructMesh s_dense.mvs

RefineMesh s_dense_mesh.mvs

TextureMesh s_dense_mesh_refine.mvs

pcd = o3d.io.read_point_cloud(reconstruction_dir+"/scene_dense_mesh_refine_texture.ply")
o3d.visualization.draw_geometries([pcd])




#!/usr/bin/python
#! -*- encoding: utf-8 -*-
import os
import subprocess
import open3d as o3d

OPENMVG_SFM_BIN = "/home/li/openMVG/openMVG_Build/Linux-x86_64-RELEASE"
OPENMVS_BIN = "/home/li/openMVS/openMVS_build/bin"


input_dir = "/home/li/frog"
output_dir = "/home/li/frog/out"
print ("Using input dir  : ", input_dir)
print ("      output_dir : ", output_dir)

if not os.path.exists(output_dir):
  os.mkdir(output_dir)

print("openMVG...")
print ("初始化文件")
pIntrisics = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_SfMInit_ImageListing"),  "-i", input_dir, "-o", output_dir, "-k","2905;0;1416;0;2905.88; 1064;0;0;1"] )
#pIntrisics = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_SfMInit_ImageListing"),  "-i", input_dir, "-o", output_dir, "-k","1429.83602;0;955.939270;0;1477.61040; 796.100478;0;0;1"] )
pIntrisics.wait()

print ("特征点计算")
pFeatures = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeFeatures"),  "-i", output_dir+"/sfm_data.json", "-o", output_dir, "-m", "SIFT", "-f" , "1"] )
pFeatures.wait()

print ("特征点匹配")
pMatches = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeMatches"),  "-i", output_dir+"/sfm_data.json", "-o", output_dir, "-f", "1", "-n", "ANNL2"] )
pMatches.wait()

reconstruction_dir = output_dir+'/'+"reconstruction_sequential"
print ("光束法平差累计式SFM")
pRecons = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_IncrementalSfM"),  "-i", output_dir+"/sfm_data.json", "-m", output_dir, "-o", reconstruction_dir] )
pRecons.wait()

print ("稀疏点云着色")
pRecons = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ComputeSfM_DataColor"),  "-i", reconstruction_dir+"/sfm_data.bin", "-o", reconstruction_dir+'/'+"colorized.ply"] )
pRecons.wait()

print("加载图片")
pRecons = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_ExportUndistortedImages"),  "-i", reconstruction_dir+"/sfm_data.bin", "-o", reconstruction_dir+'/image'] )
pRecons.wait()

print("文件转换")
pRecons = subprocess.Popen( [os.path.join(OPENMVG_SFM_BIN, "openMVG_main_openMVG2openMVS"),  "-i", reconstruction_dir+'/'+"sfm_data.bin", "-o", reconstruction_dir+"/scene.mvs"] )
pRecons.wait()

print("openMVS...")
print("稠密点云")
pRecons = subprocess.Popen( ["DensifyPointCloud",  reconstruction_dir+"/scene.mvs"] )
pRecons.wait()

print("粗网格")
pRecons = subprocess.Popen( ["ReconstructMesh",  "-d", "4", reconstruction_dir+"/scene_dense.mvs"] )
pRecons.wait()

print("细化网格")
pRecons = subprocess.Popen( ["RefineMesh",  reconstruction_dir+"/scene_dense_mesh.mvs"] )
pRecons.wait()

print("纹理贴图")
pRecons = subprocess.Popen( ["TextureMesh",  reconstruction_dir+"/scene_dense_mesh_refine.mvs"] )
pRecons.wait()

print("可视化")
pcd = o3d.io.read_point_cloud(reconstruction_dir+"/scene_dense_mesh_refine_texture.ply")
o3d.visualization.draw_geometries([pcd])




