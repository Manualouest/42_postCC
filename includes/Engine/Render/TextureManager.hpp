
#ifndef TEXTUREMANAGER_HPP
# define TEXTUREMANAGER_HPP

# include <Engine/Render/ShaderManager.hpp>
# include <Engine/Render/Objects/Texture.hpp>

# include <set>

class	TextureManager
{
	public:
		TextureManager();
		~TextureManager();

		static void	use(const std::string &textureID, const char *uniformName, const int &offset);
		static void	reset(void);
		static int	loadImage(const std::string &textureID, const char *path);
		static void	deleteImage(const std::string &textureID);

		static Texture	getTexture(const std::string &textureID);
		static int		getTextureNb(const std::string &textureID);

		static void	useArray(const char *uniformName, const int &offset);
		static void	resetArray();
		static void	makeArray(const std::set<std::string> &textureIDs);

		static void	requestTexture(const std::string &textureID) {_checkInstance(); _instance->_RequestedIds.insert(textureID);}
		static void	requestTextures(const std::set<std::string> &textureIDs) {_checkInstance(); _instance->_RequestedIds.insert(textureIDs.begin(), textureIDs.end());}
		static void	unRequestTexture(const std::string &textureID) {_checkInstance(); _instance->_RequestedIds.erase(textureID);}
		static void	makeRequestArray() {_checkInstance(); makeArray(_instance->_RequestedIds);}

	private:
		static void	_checkInstance();

		static TextureManager	*_instance;

		std::string						_currentID;
		std::map<std::string, Texture>	_textures;

		GLuint					_ArrayID = -1;
		std::set<std::string>	_RequestedIds;
};

#endif