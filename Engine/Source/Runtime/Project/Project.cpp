#include "Project.h"
#include "Serialization/ProjectSerializer.h"

const std::filesystem::path& Firebox::Project::GetProjectDirectory()
{
	FB_ASSERT(s_ActiveProject, "Project is not valid!");
	return s_ActiveProject->m_ProjectDirectory;
}

std::filesystem::path Firebox::Project::GetContentDirectory()
{
	FB_ASSERT(s_ActiveProject, "Project is not valid!");
	return GetProjectDirectory() / s_ActiveProject->m_ProjectConfig.ContentDirectory;
}

std::filesystem::path Firebox::Project::GetContentFileSystemPath(const std::filesystem::path& path)
{
	FB_ASSERT(s_ActiveProject, "Project is not valid!");
	return GetContentDirectory() / path;
}

Ref<Firebox::Project> Firebox::Project::New()
{
	s_ActiveProject = CreateRef<Project>();
	return s_ActiveProject;
}

Ref<Firebox::Project> Firebox::Project::Load(const std::filesystem::path& path)
{
	return nullptr;
}

bool Firebox::Project::SaveActiveProject(const std::filesystem::path& path)
{
	return false;
}
