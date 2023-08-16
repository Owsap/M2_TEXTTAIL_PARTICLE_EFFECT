import os
from PIL import Image

root = os.getcwd()

def gif_to_png(filename, total_frames):
	input_path = os.path.join(root, filename)
	gif_image = Image.open(input_path)

	output_folder = os.path.join(root, "effect")
	os.makedirs(output_folder, exist_ok=True)

	for frame_index in range(gif_image.n_frames):
		gif_image.seek(frame_index)
		rgba_frame = gif_image.convert("RGBA")
		output_path = os.path.join(output_folder, f"frame_{frame_index:03d}.png")
		rgba_frame.save(output_path, "PNG")
		print(f"Frame {frame_index} saved as {output_path}")

		total_frames += 1  # Increment the total frames count

	return total_frames

def batch_convert_gif_to_png():
	total_frames = 0
	for filename in os.listdir(root):
		if filename.endswith(".gif"):
			total_frames = gif_to_png(filename, total_frames)

	# Write the total_frames value to frames.txt
	frames_file_path = os.path.join(root, "frames.txt")
	with open(frames_file_path, "w") as frames_file:
		frames_file.write(str(total_frames))

	print(f"Total frames extracted: {total_frames}")

batch_convert_gif_to_png()
