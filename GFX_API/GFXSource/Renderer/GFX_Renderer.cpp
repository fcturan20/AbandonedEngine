#include "GFX_Renderer.h"
#include <string>

namespace GFX_API {
	void RenderGraph_Manager::Bind_RenderGraph(RenderGraph* RenderGraph) { RENDERGRAPH = RenderGraph; TuranAPI::LOG_STATUS("RenderGraph: " + RenderGraph->NAME + " is bound to RenderGraph Manager!"); }


	Renderer* Renderer::SELF = nullptr;

	Renderer::Renderer(): Bound_RenderGraphs(LASTUSEDALLOCATOR, 1, 1), RenderGraphIDs_toRunThisFrame(LASTUSEDALLOCATOR, 1, 1), Renderer_Context(nullptr), GraphManager(nullptr) {

	}

	Renderer::~Renderer() {
		TuranAPI::LOG_NOTCODED("GFX_Renderer Destruction isn't coded!", false);
	}

	void Renderer::Bind_RenderGraph(RenderGraph* RenderGraph) {
		SELF->Bound_RenderGraphs.push_back(RenderGraph);
		RenderGraph->Set_RenderGraphID(SELF->RenderGraph_ID_Generation());
	}

	void Renderer::Destroy_RenderGraph(unsigned int RenderGraph_ID) {
		RenderGraph* RenderGraph = SELF->Find_RenderGraph_byID(RenderGraph_ID);
		SELF->GraphManager->Bind_RenderGraph(RenderGraph);
		SELF->GraphManager->Destroy_RenderGraph();
		unsigned int vector_index = SELF->Find_RenderGraph_VectorIndex(RenderGraph->Get_RenderGraph_ID());
		SELF->Bound_RenderGraphs.erase(vector_index);
	}
	void Renderer::Run_RenderGraph_ThisFrame(unsigned int RenderGraph_ID) {
		//In final production, there will be no situation cause this error! So, run this in debug build
#ifdef TURAN_DEBUGGING
		for (unsigned int i = 0; i < SELF->RenderGraphIDs_toRunThisFrame.size(); i++) {
			unsigned int ID = SELF->RenderGraphIDs_toRunThisFrame[i];
			if (RenderGraph_ID == ID) {
				//const char* LOGTEXT = Text_Add("Renderer::Run_RenderGraph_ThisFrame is called more than one for RenderGraph_ID: ", std::to_string(RenderGraph_ID).c_str());
				TuranAPI::LOG_ERROR("There is an Error!\n");
				return;
			}
		}
#endif
		SELF->RenderGraphIDs_toRunThisFrame.push_back(RenderGraph_ID);
	}
	void Renderer::New_Frame() {
		TuranAPI::LOG_STATUS("Renderer prepares for this frame!");

		/*
		SELF->RenderGraphIDs_toRunThisFrame.clear();
		for (unsigned int i = 0; i < SELF->Bound_RenderGraphs.size(); i++) {
			RenderGraph* RENDERGRAPH = SELF->Bound_RenderGraphs[i];
			SELF->GraphManager->Bind_RenderGraph(RENDERGRAPH);
			SELF->GraphManager->NewFrame_Setup();
		}*/
	}



	
	//Helper Functions

	unsigned int Renderer::Find_RenderGraph_VectorIndex(unsigned int RenderGraph_ID) {
		for (unsigned int index = 0; index < Bound_RenderGraphs.size(); index++) {
			RenderGraph* RENDERGRAPH = Bound_RenderGraphs[index];
			if (RenderGraph_ID == RENDERGRAPH->Get_RenderGraph_ID()) {
				return index;
			}
		}
		//TuranAPI::LOG_ERROR("Renderer::Find_RenderGraph_VectorIndex() failed to find RenderGraph_ID: " + to_string(RenderGraph_ID));
		return 0;
	}
	RenderGraph* Renderer::Find_RenderGraph_byID(unsigned int RenderGraph_ID) {
		for (unsigned int i = 0; i < Bound_RenderGraphs.size(); i++) {
			RenderGraph* RENDERGRAPH = Bound_RenderGraphs[i];
			if (RenderGraph_ID == RENDERGRAPH->Get_RenderGraph_ID()) {
				return RENDERGRAPH;
			}
		}
		//TuranAPI::LOG_ERROR("Renderer::Find_RenderGraph_byID failed to find a RenderGraph by ID: " + to_string(RenderGraph_ID));
		return nullptr;
	}
	unsigned int Renderer::RenderGraph_ID_Generation() {
		TuranAPI::LOG_NOTCODED("Renderer::RenderGraph_ID_Generation() isn't coded!", true);
		return 0;
	}
}