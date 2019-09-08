#include "Texture_Resource.h"

using namespace TuranAPI::File_System;

Texture_Properties::Texture_Properties(){}
Texture_Properties::Texture_Properties(TuranAPI::TuranAPI_ENUMs dimension, TuranAPI::TuranAPI_ENUMs mipmap_filtering, TuranAPI::TuranAPI_ENUMs wrapping, TuranAPI::TuranAPI_ENUMs channel_type, TuranAPI::TuranAPI_ENUMs value_type)
	: DIMENSION(dimension), MIPMAP_FILTERING(mipmap_filtering), WRAPPING(wrapping), CHANNEL_TYPE(channel_type), VALUE_TYPE(value_type) {}


Texture_Resource::Texture_Resource() {
	ALL_TEXTUREs.push_back(this);
}

vector<Texture_Resource*> Texture_Resource::ALL_TEXTUREs = vector<Texture_Resource*>{};

TuranAPI::TuranAPI_ENUMs Texture_Resource::Get_Resource_Type() {
	return TEXTURE_RESOURCE;
}