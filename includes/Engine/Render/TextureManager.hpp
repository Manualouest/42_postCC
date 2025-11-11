
#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/Objects/Texture.hpp>

class	TextureManager
{
	public:
		TextureManager();
		~TextureManager();

		static void	use(const std::string &textureID, const char *uniformName, const int &offset);
		static void	reset(void);
		static void	loadImage(const std::string &textureID, const char *path);
		static void	deleteTexture(const std::string &textureID);
		static void	deleteTextures(const std::vector<std::string> &textureIDs);

		static Texture	getTexture(const std::string &textureID);

		static void	useArray(const std::string &arrayID, const char *uniformName, const int &offset);
		static void	resetArray();
		static void	deleteArray(const std::string &arrayID);
		static void	makeArray(const std::string &arrayID, const std::vector<std::string> &textureIDs);

	private:
		static void	_checkInstance();

		static TextureManager	*_instance;

		std::string						_currentID;
		std::map<std::string, Texture>	_textures;
		std::map<std::string, GLuint>	_arrays;
};

#endif