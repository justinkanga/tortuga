import os
import platform

COMMON_DIRS = set([
    os.path.join('packages', 'vision'),
    os.path.join('packages', 'pattern'),
    os.path.join('packages', 'core'),
    os.path.join('packages', 'math')])
#    os.path.join('wrappers', 'pattern'),
#    os.path.join('wrappers', 'core'),
#    os.path.join('wrappers', 'math'),
#    os.path.join('wrappers', 'vision'),
#    os.path.join('sandbox', 'jaus')])

LINUX_DIRS = set([
    os.path.join('packages','extensions', 'wxogre'),
    os.path.join('packages', 'vehicle'),
    os.path.join('packages', 'sensorapi'),
    os.path.join('packages', 'thrusterapi'),
    os.path.join('packages', 'carnetix'),
    os.path.join('packages', 'imu'),
    os.path.join('packages', 'control'),
#    os.path.join('wrappers', 'control'),
#    os.path.join('wrappers', 'vehicle'),
    os.path.join('tools', 'MagInclination'),
    os.path.join('tools', 'BiasFinder')])

MAC_DIRS = set([])

def get_dirs():
    """
    Returns the directories to build for the current platform, uses pythons 
    platform.system() function.
    """
    dirs = set()
    dirs.update(COMMON_DIRS)

    # Add directories based on platform (to be changed later)
    added_dirs = set()
    if platform.system() == 'Linux':
        added_dirs = LINUX_DIRS
    elif platform.system() == 'Darwin':
        added_dirs = MAC_DIRS

    # If there is an intersection between the directories warn the user to fix
    # it and then continue with the build
    intersection = dirs.intersection(added_dirs)
    dirs.update(added_dirs)

    if 0 != len(intersection):
        print 'WARNING duplicate directories:',' '.join(intersection)
        print 'Please edit buildfiles/dirs_to_build.py'

    return dirs
