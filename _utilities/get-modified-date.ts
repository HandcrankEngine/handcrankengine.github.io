import util from 'node:util';
import child_process from 'node:child_process';

const exec = util.promisify(child_process.exec);

const getModifiedDate = async (path: string) => {
  const { stdout: lastModified } = await exec(
    `git log -1 --pretty="format:%ci" ${path}`
  );

  return lastModified ? new Date(lastModified) : new Date();
};

export default getModifiedDate;
