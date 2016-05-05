#!/bin/bash
rostopic pub -1 /gains std_msgs/Float64MultiArray '{layout: {dim: [{label: "x", size: 3, stride: 3}], data_offset: 0}, data: ['$1', '$2', '$3', '$4']}'
