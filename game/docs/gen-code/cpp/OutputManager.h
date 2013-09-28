namespace com {
	namespace dragon3d {
		namespace output {
			class OutputManager : com::dragon3d::framework::Output {
		

			public:
				void registerDevice();
			
				void output(com::dragon3d::framework::Scene scene);
			
				void registerController();
			
				void getControllerByDevice();
			};
		}
	}
}
