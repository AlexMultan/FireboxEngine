#pragma once

#include "ProjectConfig.h"

namespace Firebox {

	class FIREBOX_API Project : public RefCounted
	{
	public:
		static const std::filesystem::path& GetProjectDirectory();
		static std::filesystem::path GetContentDirectory();
		static std::filesystem::path GetContentFileSystemPath(const std::filesystem::path& path);

		inline static Ref<Project> GetActiveProject() { return s_ActiveProject; }
		inline const ProjectConfig& GetConfig() const { return m_ProjectConfig; }

		static Ref<Project> New();
		static Ref<Project> Load(const std::filesystem::path& path);
		static bool SaveActiveProject(const std::filesystem::path& path);

	private:
		ProjectConfig m_ProjectConfig;
		std::filesystem::path m_ProjectDirectory;
		inline static Ref<Project> s_ActiveProject;
	};
}