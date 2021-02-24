cmake_minimum_required(VERSION 3.10)

set(IMAGES
        )

file(COPY ${IMAGES} DESTINATION ./)

set(OPENDRIVE
        highway_north.xodr
        highway_exit_south.xodr
        )
file(COPY ${OPENDRIVE} DESTINATION ./)