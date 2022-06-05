CC = g++
CFLAGS = -Wall -std=c++11
INC_PATH = -I /Library/Frameworks/SDL2.framework/Headers
LDFLAGS = -l SDL2-2.0.0

trancengine: main.o
	$(CC) $(CFLAGS) $(INC_PATH) $(LDFLAGS) -framework OpengL bin/main.o bin/Renderer.o bin/VertexBuffer.o bin/IndexBuffer.o bin/VertexArray.o bin/Shader.o bin/Game.o bin/Vector2D.o bin/AssetManager.o bin/Ball.o bin/Collision.o bin/ObjectManager.o bin/Edge.o bin/Spring.o bin/Line.o bin/SoftBody.o bin/Circle.o -o play

main.o: main.cpp bin/Renderer.o bin/VertexBuffer.o bin/IndexBuffer.o bin/VertexArray.o bin/Shader.o bin/Game.o bin/Vector2D.o bin/AssetManager.o bin/Ball.o bin/Collision.o bin/ObjectManager.o bin/Edge.o bin/Spring.o bin/Line.o bin/SoftBody.o bin/Circle.o
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

bin/Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) $(INC_PATH) Game.cpp -c -o bin/Game.o

bin/Vector2D.o: Vector2D.cpp Vector2D.h
	$(CC) $(CFLAGS) $(INC_PATH) Vector2D.cpp -c -o bin/Vector2D.o

bin/AssetManager.o: AssetManager.cpp AssetManager.h
	$(CC) $(CFLAGS) $(INC_PATH) AssetManager.cpp -c -o bin/AssetManager.o

bin/Ball.o: Ball.cpp Ball.h
	$(CC) $(CFLAGS) $(INC_PATH) Ball.cpp -c -o bin/Ball.o

bin/Collision.o: Collision.cpp Collision.h
	$(CC) $(CFLAGS) $(INC_PATH) Collision.cpp -c -o bin/Collision.o

bin/ObjectManager.o: ObjectManager.cpp ObjectManager.h
	$(CC) $(CFLAGS) $(INC_PATH) ObjectManager.cpp -c -o bin/ObjectManager.o

bin/Edge.o: Edge.cpp Edge.h
	$(CC) $(CFLAGS) $(INC_PATH) Edge.cpp -c -o bin/Edge.o

bin/Spring.o: Spring.cpp Spring.h
	$(CC) $(CFLAGS) $(INC_PATH) Spring.cpp -c -o bin/Spring.o

bin/Line.o: Line.cpp Line.h
	$(CC) $(CFLAGS) $(INC_PATH) Line.cpp -c -o bin/Line.o

bin/SoftBody.o: SoftBody.cpp SoftBody.h
	$(CC) $(CFLAGS) $(INC_PATH) SoftBody.cpp -c -o bin/SoftBody.o

bin/Circle.o: Circle.cpp Circle.h
	$(CC) $(CFLAGS) $(INC_PATH) Circle.cpp -c -o bin/Circle.o

clean :
	-rm *.o bin/*.o play