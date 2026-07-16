

## Dependências (Ubuntu 20.04 + ROS Noetic)

```bash
sudo apt-get update
sudo apt-get install \
  ros-noetic-turtlebot3 \
  ros-noetic-turtlebot3-gazebo \
  ros-noetic-turtlebot3-navigation \
  ros-noetic-turtlebot3-description \
  ros-noetic-gmapping \
  ros-noetic-amcl \
  ros-noetic-move-base \
  ros-noetic-map-server \
  ros-noetic-navigation \
  ros-noetic-robot-state-publisher \
  ros-noetic-tf2-ros \
  ros-noetic-dwa-local-planner
```

## Configurar modelo do TurtleBot3

Adicione ao `~/.bashrc`:
```bash
export TURTLEBOT3_MODEL=burger
source /opt/ros/noetic/setup.bash
```

## RRT Exploration (Python 3)

O pacote original `hasauino/rrt_exploration` usa Python 2.
Clone o fork compatível com Noetic:

```bash
cd ~/catkin_ws/src
git clone https://github.com/hasauino/rrt_exploration.git
```

Corrija os scripts Python para Python 3 (shebang e print):
```bash
sed -i 's|#!/usr/bin/env python$|#!/usr/bin/env python3|g' \
  rrt_exploration/scripts/filter.py \
  rrt_exploration/scripts/assigner.py
```

## Build

```bash
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
# Copie a pasta eco-bot-noetic aqui como "ecobot"
cp -r /path/to/eco-bot-noetic ~/catkin_ws/src/ecobot
git clone https://github.com/hasauino/rrt_exploration.git
cd ~/catkin_ws
catkin_make
source devel/setup.bash
```

## Executar

### 1. Gerar Mapa
```bash
source devel/setup.bash
roslaunch ecobot Mapping.launch
```
No RViz, publique 4 pontos (limites da área) + 1 interno.

### 2. Salvar Mapa
```bash
rosrun map_server map_saver -f ~/catkin_ws/src/ecobot/data/maps/CollectorSpace
```

### 3. Coletar Lixo
```bash
source devel/setup.bash
roslaunch ecobot Collecting.launch
# Em outro terminal:
rosrun ecobot trash
```


