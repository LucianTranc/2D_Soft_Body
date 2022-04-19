CC = g++
CFLAGS = -Wall -std=c++11
INC_PATH = -I /Library/Frameworks/SDL2.framework/Headers -I /Library/Frameworks/SDL2_image.framework/Headers -I /Library/Frameworks/SDL2_ttf.framework/Headers
LDFLAGS = -l SDL2-2.0.0 -l SDL2_image-2.0.0 -l SDL2_ttf-2.0.0

trancengine: main.o
	$(CC) $(CFLAGS) $(INC_PATH) $(LDFLAGS) -framework OpengL bin/main.o bin/Renderer.o bin/VertexBuffer.o bin/IndexBuffer.o bin/VertexArray.o bin/Shader.o bin/Texture.o bin/Game.o bin/Vector2D.o bin/AssetManager.o bin/TextureManager.o bin/Ball.o bin/Collision.o bin/BallManager.o bin/Edge.o bin/Hole.o bin/Table.o bin/Cue.o -o play

main.o: main.cpp bin/Renderer.o bin/VertexBuffer.o bin/IndexBuffer.o bin/VertexArray.o bin/Shader.o bin/Texture.o bin/stb_image.o bin/Game.o bin/Vector2D.o bin/AssetManager.o bin/TextureManager.o bin/Ball.o bin/Collision.o bin/BallManager.o bin/Edge.o bin/Hole.o bin/Table.o bin/Cue.o
	$(CC) $(CFLAGS) $(INC_PATH) main.cpp -c -o bin/main.o

bin/Renderer.o: Renderer.cpp Renderer.h
	$(CC) $(CFLAGS) $(INC_PATH) Renderer.cpp -c -o bin/Renderer.o

bin/VertexBuffer.o: VertexBuffer.cpp VertexBuffer.h
	$(CC) $(CFLAGS) $(INC_PATH) VertexBuffer.cpp -c -o bin/VertexBuffer.o

bin/IndexBuffer.o: IndexBuffer.cpp IndexBuffer.h
	$(CC) $(CFLAGS) $(INC_PATH) IndexBuffer.cpp -c -o bin/IndexBuffer.o

bin/VertexArray.o: VertexArray.cpp VertexArray.h
	$(CC) $(CFLAGS) $(INC_PATH) VertexArray.cpp -c -o bin/VertexArray.o

bin/Shader.o: Shader.cpp Shader.h
	$(CC) $(CFLAGS) $(INC_PATH) Shader.cpp -c -o bin/Shader.o

bin/Texture.o: Texture.cpp Texture.h
	$(CC) $(CFLAGS) $(INC_PATH) Texture.cpp -c -o bin/Texture.o

bin/stb_image.o: vendor/stb_image/stb_image.cpp vendor/stb_image/stb_image.h
	$(CC) $(CFLAGS) $(INC_PATH) vendor/stb_image/stb_image.cpp -c -o bin/stb_image.o

bin/Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) $(INC_PATH) Game.cpp -c -o bin/Game.o

bin/Vector2D.o: Vector2D.cpp Vector2D.h
	$(CC) $(CFLAGS) $(INC_PATH) Vector2D.cpp -c -o bin/Vector2D.o

bin/AssetManager.o: AssetManager.cpp AssetManager.h
	$(CC) $(CFLAGS) $(INC_PATH) AssetManager.cpp -c -o bin/AssetManager.o

bin/TextureManager.o: TextureManager.cpp TextureManager.h
	$(CC) $(CFLAGS) $(INC_PATH) TextureManager.cpp -c -o bin/TextureManager.o

bin/Ball.o: Ball.cpp Ball.h
	$(CC) $(CFLAGS) $(INC_PATH) Ball.cpp -c -o bin/Ball.o

bin/Collision.o: Collision.cpp Collision.h
	$(CC) $(CFLAGS) $(INC_PATH) Collision.cpp -c -o bin/Collision.o

bin/BallManager.o: BallManager.cpp BallManager.h
	$(CC) $(CFLAGS) $(INC_PATH) BallManager.cpp -c -o bin/BallManager.o

bin/Edge.o: Edge.cpp Edge.h
	$(CC) $(CFLAGS) $(INC_PATH) Edge.cpp -c -o bin/Edge.o

bin/Hole.o: Hole.cpp Hole.h
	$(CC) $(CFLAGS) $(INC_PATH) Hole.cpp -c -o bin/Hole.o

bin/Table.o: Table.cpp Table.h
	$(CC) $(CFLAGS) $(INC_PATH) Table.cpp -c -o bin/Table.o

bin/Cue.o: Cue.cpp Cue.h
	$(CC) $(CFLAGS) $(INC_PATH) Cue.cpp -c -o bin/Cue.o

clean :
	-rm *.o bin/*.o play