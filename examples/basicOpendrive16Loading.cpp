//
// Created by brucknem on 24.06.21.
//
#include "opendrive_1_6/opendrive_16_core.hxx"

int main(int argc, char **argv) {
    *simulation::standard::opendrive_schema::OpenDRIVE_("../misc/test_map_opendrive_1_6.xodr",
                                                        ::xml_schema::flags::dont_validate);
}